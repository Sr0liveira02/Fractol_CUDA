/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_fractols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42lisba.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:51:48 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/21 13:46:20 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"
#include "sys/time.h"

__host__ int 	fractol_formula(t_mlx_data *data)
{
	double	ind;
	double	real;

	ind = 0;
	while (ind++ < data->sc)
	{
		real = (data->n.z_r * data->n.z_r) - \
			(data->n.z_i * data->n.z_i) + data->n.c_r;
		data->n.z_i = (data->n.z_r * data->n.z_i * 2) + data->n.c_i;
		data->n.z_r = real;
		if ((data->n.z_r * data->n.z_r) + \
			(data->n.z_i * data->n.z_i) > 4)
		{
			if (data->col == XK_1 || data->col == XK_2 || data->col == XK_3)
				return ((((int)(((ind / data->sc)) * 255))) <<
				(8 * (data->col == XK_2) + 16 * (data->col == XK_3)));
			else if (data->col == XK_4)
				return ((ind / data->sc) * 16777216);
			else if (data->col == XK_5)
				return ((1 - (ind / data->sc)) * 16777216);
			return (data->a + data->b * cos(2 * 3.14159 \
				* (data->c * (ind / 100) + data->d)));
		}
	}
	return (0);
}

__device__ int fractol_formula_cuda(
    double z_r, double z_i, double c_r, double c_i,
    int sc, int col, double a, double b, double c, double d
) {
    double ind = 0;
    double real;
    while (ind++ < sc) {
        real = (z_r * z_r) - (z_i * z_i) + c_r;
        z_i = (z_r * z_i * 2) + c_i;
        z_r = real;
        if ((z_r * z_r) + (z_i * z_i) > 4) {
            if (col == XK_1 || col == XK_2 || col == XK_3)
                return ((((int)(((ind / sc)) * 255))) <<
                        (8 * (col == XK_2) + 16 * (col == XK_3)));
            else if (col == XK_4)
                return ((ind / sc) * 16777216);
            else if (col == XK_5)
                return ((1 - (ind / sc)) * 16777216);
            return (a + b * cos(2 * 3.14159 * (c * (ind / 100) + d)));
        }
    }
    return 0;
}

__global__ void julia_set(
    int *matrix, int width, int height,
    double x_mult, double y_mult,
    double x_cords, double y_cords,
    double real, double imag,
    int sc, int col, double a, double b, double c, double d
) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    if (x < width && y < height) {
        double z_r = ((x * x_mult / width)) - x_cords;
        double z_i = y_cords - ((y * y_mult) / height);
        double c_r = real;
        double c_i = imag;
        matrix[y * width + x] = fractol_formula_cuda(
            z_r, z_i, c_r, c_i, sc, col, a, b, c, d
        );
    }
}

__global__ void mandelbrot(
    int *matrix, int width, int height,
    double x_mult, double y_mult,
    double x_cords, double y_cords,
    int sc, int col, double a, double b, double c, double d
) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    if (x < width && y < height) {
        double z_r = 0.0;
        double z_i = 0.0;
        double c_r = ((x * x_mult / width)) - x_cords;
        double c_i = y_cords - ((y * y_mult) / height);
        matrix[y * width + x] = fractol_formula_cuda(
            z_r, z_i, c_r, c_i, sc, col, a, b, c, d
        );
    }
}

__host__ void show_frame(t_mlx_data *data) {
	int	x;
	int	y;
	int	w;
	int	h;

	y = -1;
	w = WIDTH;
	h = HIGHT;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
		{
			my_put_pixel(&data->img, x, y, data->matrix[y * WIDTH + x]);
		}
	}
	aux_mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
}

__host__ void	j_m_bs(t_mlx_data *data)
{
	dim3 block(16, 16);
	dim3 grid((WIDTH + block.x - 1) / block.x, (HIGHT + block.y - 1) / block.y);

	// calculate with GPU
	if (data->flag == 1)
		julia_set<<<grid, block>>>(
			data->matrix, WIDTH, HIGHT,
			data->x_mult, data->y_mult,
			data->x_cords, data->y_cords,
			data->real, data->i,
			data->sc, data->col, data->a, data->b, data->c, data->d
		);
	else if (data->flag == 0)
		mandelbrot<<<grid, block>>>(
			data->matrix, WIDTH, HIGHT,
			data->x_mult, data->y_mult,
			data->x_cords, data->y_cords,
			data->sc, data->col, data->a, data->b, data->c, data->d
		);
	else
		burning_ship(data);


	// wait
	cudaDeviceSynchronize();
	
	// show frame
	show_frame(data);

}

__host__ void create_matrix(int** matrix) {
	int count = 0;
	cudaGetDeviceCount(&count);
	printf("CUDA device count: %d\n", count);
	if (count == 0) {
		fprintf(stderr, "No CUDA devices found!\n");
		exit(1);
	}
    cudaMallocManaged(matrix, WIDTH * HIGHT * sizeof(int));
    int device = -1;
	cudaError_t err = cudaGetDevice(&device);
	printf("cudaGetDevice returned %d, device = %d\n", err, device);
	cudaMemPrefetchAsync(*matrix, WIDTH * HIGHT * sizeof(int), device, 0);
}

__host__ void delete_matrix(int* matrix) {
	cudaFree(matrix);
}

/*int	second_julia_set(t_mlx_data *data, float r, float i)
{
	double	x;
	double	y;
	double	w;
	double	h;

	y = -1;
	w = WIDTH;
	h = HIGHT;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
		{
			data->n.z_r = ((x * 2.65 / w)) - 1.325;
			data->n.z_i = 1.25 - ((y * 2.5) / h);
			data->n.c_r = r;
			data->n.c_i = i;
			my_put_pixel(&data->img2, x, y, fractol_formula(data));
		}
	}
	mlx_put_image_to_window
	(data->mlx_ptr, data->win_ptr2, data->img2.img_ptr, 0, 0);
	return (0);
}*/