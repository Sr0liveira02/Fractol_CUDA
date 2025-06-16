/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:57:21 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/16 17:58:31 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	zoom(t_mlx_data *data, int flag)
{
	data->x_cords -= flag * data->x_mult / (20 + 2 * (flag == 1));
	data->y_cords -= flag * data->y_mult / (20 + 2 * (flag == 1));
	data->x_mult -= flag * data->x_mult / (10 + (flag == 1));
	data->y_mult -= flag * data->y_mult / (10 + (flag == 1));
	if (data->flag)
		julia_set(data);
	else
		mandelbrot(data);
}

void	mouse_zoom(t_mlx_data *data, int x, int y, int flag)
{
	float	rx;
	float	ry;

	rx = x;
	ry = y;
	data->x_cords += flag * ((data->x_mult / 10) * (rx / WIDTH));
	data->y_cords += flag * (data->y_mult / 10) * (ry / HIGHT);
	data->x_mult += flag * (data->x_mult / 10);
	data->y_mult += flag * (data->y_mult / 10);
	if (data->flag)
		julia_set(data);
	else
		mandelbrot(data);
}
