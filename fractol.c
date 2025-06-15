/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:17:36 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/15 01:12:05 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	fractol_formula(double z_real, double z_i, double c_real, double c_i)
{
	float		ind;
	double		real;

	ind = -1;
	while (ind++ < 100)
	{
		real = (z_real * z_real) - (z_i * z_i) + c_real;
		z_i = (z_real * z_i * 2) + c_i;
		z_real = real;
		if ((z_real * z_real) + (z_i * z_i) > 4)
			return (16581375 * (1 / ind));
	}
	return (0);
}

void	set_data(t_mlx_data *data, int ac, char **av)
{
	data->av = av;
	data->x_mult = 2.65;
	data->y_mult =  2.5;
	data->y_cords = 1.25;
	if (ac == 3)
	{
		data->real = atof(av[1]);
		data->i = atof(av[2]);
		data->flag = 1;
		data->x_cords = 1.325;
		return ;
	}
	data->x_cords = 2.1;
	data->real = 0;
	data->i = 0;
	data->flag = 0;

}
int	exit_func(t_mlx_data *data)
{
	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->win_ptr2)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr2);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	if (data->mlx_ptr)
		free (data->mlx_ptr);
	exit (1);
}

void	my_put_pixel(t_image *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->pixel_ptr)) = color;
}

// int	color_code(float *d)
// {
// 	// int	r;
// 	// int	g;
// 	// int	b;
// 	// 
// 	// r = 9 * (1 - t) * t * t * t * 255;
// 	// g = 15 * (1 - t) * (1 - t) * t * t * 255;
// 	// b = 8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255;
		
// 	return (0);
// }

int	Julia_set(t_mlx_data *data)
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
			my_put_pixel(&data->img, x, y, 
				fractol_formula(((x * data->x_mult / w)) - data->x_cords,
				data->y_cords - ((y * data->y_mult) / h), data->real, data->i));
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0 , 0);
	return (0);
}

int	Mandelbrot(t_mlx_data *data)
{
	double	x;
	double	y;
	double	w;
	double	h;

	y = -1;
	w = WIDTH;
	h = HIGHT;
	printf("%f, %f\n", data->real, data->i);
	while (++y < h)
	{
		x = -1;
		while (++x < w)
		{
			my_put_pixel(&data->img, x, y, 
				fractol_formula(0, 0, ((x * data->x_mult / w)) - data->x_cords,
				data->y_cords - ((y * data->y_mult) / h)));
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0 , 0);
	return (0);
}

void	my_cpy_pixel_vert(t_image *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->pixel_ptr)) = *((unsigned int *)(offset + img->pixel_ptr + (img->line_len * color)));
}

int	go_func(t_mlx_data *data, double x, double y)
{
	double	w;
	double	h;

	w = WIDTH;
	h = HIGHT;
	if (data->flag)
		return (fractol_formula(((x * data->x_mult / w)) - data->x_cords,
		data->y_cords- ((y * data->y_mult) / h), data->real, data->i));
	else
		return (fractol_formula(0, 0, ((x * data->x_mult / w)) - data->x_cords,
		data->y_cords- ((y * data->y_mult) / h)));
}

void	go_up(t_mlx_data *data, int divide)
{
	double	x;
	double	y;
	double	w;
	double	h;

	w = WIDTH;
	h = HIGHT;
	y = -1;
	data->y_cords -= (data->y_mult / divide);
	while (++y <= h)
	{
		x = -1;
		if (y < (h * 9 / 10))
			while (++x < w)
				my_cpy_pixel_vert(&data->img, x, y, (h / 10));
		else
			while (++x < w)
				my_put_pixel(&data->img, x, y, go_func(data, x, y));
	}
}

void	go_down(t_mlx_data *data, int divide)
{
	double	x;
	double	y;
	double	w;
	double	h;

	w = WIDTH;
	h = HIGHT;
	x = 0;
	y = HIGHT;
	data->y_cords += (data->y_mult / divide);
	while (--y > 0)
	{
		x = -1;
		if (y > h / 10)
			while (++x < w)
				my_cpy_pixel_vert(&data->img, x, y, - (h / 10));
		else
			while (++x < w)
				my_put_pixel(&data->img, x, y, go_func(data, x, y));
	}
}

void	my_cpy_pixel_hori(t_image *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->pixel_ptr)) = *((unsigned int *)(offset + img->pixel_ptr + ((img->bpp / 8) * color)));
}

void	go_left(t_mlx_data *data, int divide)
{
	double	x;
	double	y;
	double	w;
	double	h;

	w = WIDTH;
	h = HIGHT;
	y = 0;
	data->x_cords -= (data->x_mult / divide);
	while (y < h)
	{
		x = 0;
		while (x < w * 9 / 10)
		{
			my_cpy_pixel_hori(&data->img, x, y, (w / 10));
			x++;
		}
		x--;
		while (++x <= w)
			my_put_pixel(&data->img, x, y, go_func(data, x, y));
		y++;
	}
}

void	go_right(t_mlx_data *data, int divide)
{
	double	x;
	double	y;
	double	w;
	double	h;

	w = WIDTH;
	h = HIGHT;
	y = 0;
	data->x_cords += (data->x_mult / divide);
	while (y < h)
	{
		x = w + 1;
		while (--x > w / 10)
			my_cpy_pixel_hori(&data->img, x, y, - (w / 10));
		x++;
		while (x-- > 0)
			my_put_pixel(&data->img, x, y, go_func(data, x, y));
		y++;
	}
}

void	zoom(t_mlx_data *data, int flag)
{
	data->x_cords -= flag * data->x_mult / (20 + 2 * (flag == 1));
	data->y_cords -= flag * data->y_mult / (20 + 2 * (flag == 1));
	data->x_mult -= flag * data->x_mult / (10 + (flag == 1));
	data->y_mult -= flag * data->y_mult / (10 + (flag == 1));
	if (data->flag)
		Julia_set(data);
	else
		Mandelbrot(data);
}

void	Julia_or_Mandelbrot(t_mlx_data *data)
{
	if (data->flag)
		Julia_set(data);
	else
		Mandelbrot(data);
}

int	key_hook(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
		exit_func(data);
	if (keysym == XK_space)
		set_data(data, data->ac, data->av);
	if (keysym == XK_space)
		Julia_or_Mandelbrot(data);
	if (keysym == XK_Down)
		go_up(data, 10);
	if (keysym == XK_Up)
		go_down(data, 10);
	if (keysym == XK_Right)
		go_left(data, 10);
	if (keysym == XK_Left)
		go_right(data, 10);
	if (keysym == XK_KP_Add)
		zoom(data, 1);
	if (keysym == XK_KP_Subtract)
		zoom(data, -1);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0 , 0);
	return (0);
}

void	mouse_zoom(t_mlx_data *data, int x, int y, int flag)
{
	float	rx;
	float	ry;

	rx = x;
	ry = y;
	data->x_cords += flag * (data->x_mult / 10) * (rx / WIDTH);
	data->y_cords += flag * (data->y_mult / 10) * (ry / HIGHT);
	data->x_mult += flag * (data->x_mult / 10);
	data->y_mult += flag * (data->y_mult / 10);
	if (data->flag)
		Julia_set(data);
	else
		Mandelbrot(data);
}


int	second_Julia_set(t_mlx_data *data, t_image *img, float r, float i)
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
			my_put_pixel(img, x, y, 
				fractol_formula(((x * data->x_mult / w)) - data->x_cords,
				data->y_cords - ((y * data->y_mult) / h), r, i));
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr2, data->img.img_ptr, 0 , 0);
	return (0);
}

int	mouse_hook(int keysym, int x, int y,t_mlx_data *data)
{
	float	rx;
	float	ry;

	rx = x;
	ry = y;
	if (keysym == 1)
	{
		if (data->win_ptr2 == NULL)
			data->win_ptr2 = mlx_new_window(data->mlx_ptr, WIDTH, HIGHT, "Julia_set");
		if (data->win_ptr2 == NULL)
			exit_func(data);
		second_Julia_set(data, &data->img, (rx * data->x_mult / WIDTH) - data->x_cords, data->y_cords - ((ry * data->y_mult) / HIGHT));
	}
	if (keysym == 4)
		mouse_zoom(data, x, y, -1);
	if (keysym == 5)
		mouse_zoom(data, x, y, 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_mlx_data	data;

	set_data(&data, ac, av);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	data.win_ptr2 = NULL;
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIDTH, HIGHT, "fractol");
	if (data.win_ptr == NULL)
		return (mlx_destroy_display(data.mlx_ptr), free (data.mlx_ptr), 1);
	data.img.img_ptr = mlx_new_image(data.mlx_ptr, WIDTH, HIGHT);
	data.img.pixel_ptr = mlx_get_data_addr
	(data.img.img_ptr, &data.img.bpp, &data.img.line_len, &data.img.endian);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, key_hook, &data);
	mlx_hook(data.win_ptr, ButtonPress, ButtonPressMask, mouse_hook, &data);
	fflush(stdout);
	Julia_or_Mandelbrot(&data);
	mlx_loop(data.mlx_ptr);
}
