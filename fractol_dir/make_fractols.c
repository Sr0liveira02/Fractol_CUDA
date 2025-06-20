/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_fractols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:51:48 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/20 13:05:27 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	fractol_formula(t_mlx_data *data)
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
			(data->n.z_i * data->n.z_i) > data->sc)
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

int	julia_set(t_mlx_data *data)
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
			data->n.z_r = ((x * data->x_mult / w)) - data->x_cords;
			data->n.z_i = data->y_cords - ((y * data->y_mult) / h);
			data->n.c_r = data->real;
			data->n.c_i = data->i;
			my_put_pixel(&data->img, x, y, fractol_formula(data));
		}
	}
	mlx_put_image_to_window
	(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
	return (0);
}

int	mandelbrot(t_mlx_data *data)
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
			data->n.z_r = 0;
			data->n.z_i = 0;
			data->n.c_r = ((x * data->x_mult / w)) - data->x_cords;
			data->n.c_i = data->y_cords - ((y * data->y_mult) / h);
			my_put_pixel(&data->img, x, y, fractol_formula(data));
		}
	}
	mlx_put_image_to_window
		(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
	return (0);
}

void	j_m_bs(t_mlx_data *data)
{
	if (data->flag == 1)
		julia_set(data);
	else if (data->flag == 0)
		mandelbrot(data);
	else
		burning_ship(data);
}

int	second_julia_set(t_mlx_data *data, float r, float i)
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
			data->n.z_r = ((x * data->x_mult / w)) - 1.325;
			data->n.z_i = data->y_cords - ((y * data->y_mult) / h);
			data->n.c_r = r;
			data->n.c_i = i;
			my_put_pixel(&data->img2, x, y, fractol_formula(data));
		}
	}
	mlx_put_image_to_window
	(data->mlx_ptr, data->win_ptr2, data->img2.img_ptr, 0, 0);
	return (0);
}
