/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_funcs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:50:18 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/20 12:49:14 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

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
	while (y <= h)
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
	while (y <= h)
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

int	go_func(t_mlx_data *data, double x, double y)
{
	double	w;
	double	h;

	w = WIDTH;
	h = HIGHT;
	if (data->flag == 1)
	{
		data->n.z_r = ((x * data->x_mult / w)) - data->x_cords;
		data->n.z_i = data->y_cords - ((y * data->y_mult) / h);
		data->n.c_r = data->real;
		data->n.c_i = data->i;
	}
	else
	{
		data->n.z_r = 0;
		data->n.z_i = 0;
		data->n.c_r = ((x * data->x_mult / w)) - data->x_cords;
		data->n.c_i = data->y_cords - ((y * data->y_mult) / h);
	}
	if (data->flag == 0 || data->flag == 1)
		return (fractol_formula(data));
	return (bs_fractol_formula(data));
}
