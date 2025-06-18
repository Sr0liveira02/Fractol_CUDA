/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:46:46 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/18 13:26:51 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	color_code(int key, t_mlx_data *data)
{
	data->col = key;
	if (key == XK_7)
	{
		data->a = (((int)(0.938 * 255)) << 16) + (((int)(0.328 * 255)) << 8) + \
			((int)(0.718 * 255));
		data->b = (((int)(0.659 * 255)) << 16) + (((int)(0.438 * 255)) << 8) + \
			((int)(0.328 * 255));
		data->c = (((int)(0.388 * 255)) << 16) + (((int)(0.388 * 255)) << 8) + \
			((int)(0.296 * 255));
		data->d = (((int)(2.538 * 255)) << 16) + (((int)(2.478 * 255)) << 8) + \
			((int)(0.168 * 255));
	}
	if (key == XK_6)
	{
		data->a = (((int)(0)) << 16) + (((int)(125.5)) << 8) + ((int)(125.5));
		data->b = (((int)(0)) << 16) + (((int)(125.5)) << 8) + ((int)(125.5));
		data->c = (((int)(0)) << 16) + (((int)(125.5)) << 8) + ((int)(85));
		data->d = (((int)(0)) << 16) + (((int)(125.5)) << 8) + ((int)(170));
	}
	julia_or_mandelbrot(data);
	if (data->win_ptr2 != NULL)
		second_julia_set(data, data->lr, data->li);
}

void	restart_data(t_mlx_data *data, int ac, char **av)
{
	data->av = av;
	data->x_mult = 2.65;
	data->y_mult = 2.5;
	data->y_cords = 1.25;
	if (av != NULL)
		data->col = XK_1;
	data->sc = 50;
	if (ac == 4)
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
	if (data->img2.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img2.img_ptr);
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

void	data_set(t_mlx_data *data, float rx, float ry)
{
	data->x_mult = 2.65;
	data->y_mult = 2.5;
	data->y_cords = 1.25;
	data->real = rx;
	data->i = ry;
	data->flag = 1;
	data->x_cords = 1.325;
}

void	init_fractol(t_mlx_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		exit_func(data);
	data->win_ptr2 = NULL;
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HIGHT, "fractol");
	if (data->win_ptr == NULL)
		exit_func(data);
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HIGHT);
	if (data->img.img_ptr == NULL)
		exit_func(data);
	data->img.pixel_ptr = mlx_get_data_addr(data->img.img_ptr,
			&data->img.bpp, &data->img.line_len, &data->img.endian);
	if (data->img.pixel_ptr == NULL)
		exit_func(data);
	data->img2.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HIGHT);
	if (data->img2.img_ptr == NULL)
		exit_func(data);
	data->img2.pixel_ptr = mlx_get_data_addr(data->img2.img_ptr,
			&data->img2.bpp, &data->img2.line_len, &data->img2.endian);
	if (data->img2.pixel_ptr == NULL)
		exit_func(data);
}
