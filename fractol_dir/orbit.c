/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orbit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:42:49 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/16 17:58:34 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	check_color(t_image *img, float x, float y)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	return (*((unsigned int *)(offset + img->pixel_ptr)) != 0);
}

static void	my_put_pixel_lines(t_image *img, int x, int y)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->pixel_ptr)) = 16777215;
}

static void	draw_line(t_mlx_data *data, t_comp v, double a, double b)
{
	double	x;
	double	y;

	y = v.i_min - 1;
	while (++y < v.i_max)
	{
		x = (y - b) / a;
		my_put_pixel_lines(&data->img, x, y);
	}
	x = v.r_min - 1;
	while (++x < v.r_max && x < HIGHT - 1 && x > 0)
	{
		y = a * x + b;
		my_put_pixel_lines(&data->img, x, y);
	}
	mlx_put_image_to_window
	(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
}

static int	get_formula(t_comp z1, t_comp z2, t_mlx_data *data)
{
	double	a;
	double	b;
	t_comp	v;

	a = WIDTH;
	b = HIGHT;
	z1.real = (z1.real + data->x_cords) * (a / data->x_mult);
	z2.real = (z2.real + data->x_cords) * (a / data->x_mult);
	z1.i = (data->y_cords - z1.i) * (b / data->y_mult);
	z2.i = (data->y_cords - z2.i) * (b / data->y_mult);
	a = ((z1.i - z2.i) / (z1.real - z2.real));
	b = z1.i - a * (z1.real);
	v.i_min = z1.i * (z1.i < z2.i) + z2.i * (z1.i > z2.i);
	v.i_max = z2.i * (z1.i < z2.i) + z1.i * (z1.i > z2.i);
	v.r_max = z1.real * (z1.real > z2.real) + z2.real * (z1.real < z2.real);
	v.r_min = z2.real * (z1.real > z2.real) + z1.real * (z1.real < z2.real);
	if (v.r_max >= WIDTH || v.r_min <= 0 || v.i_min <= 0 || v.i_max >= HIGHT)
		return (1);
	return (draw_line(data, v, a, b), 0);
}

void	draw_orbit(t_mlx_data *data, float c_real, float c_i)
{
	t_comp	z1;
	t_comp	z2;
	float	real;
	int		ind;

	ind = -1;
	z2.real = 0;
	z2.i = 0;
	z1.real = 0;
	z1.i = 0;
	while (++ind < 150)
	{
		real = (z2.real * z2.real) - (z2.i * z2.i) + c_real;
		z2.i = (z2.real * z2.i * 2) + c_i;
		z2.real = real;
		if (get_formula(z1, z2, data))
			return ;
		z1.real = z2.real;
		z1.i = z2.i;
	}
}
