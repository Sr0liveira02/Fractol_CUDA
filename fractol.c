/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:17:36 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/16 02:55:46 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int	colors_blue(float t)
{
	int	r;
	int	g;
	int	b;

	r = 9 * (1 - t) * t * t * t * 255;
	g = 16 * (1 - t) * (1 - t) * t * t * 255;
	b = 8 * (1 - t) * (1 - t) * (1 - t) * t * 255;
	return (b);
}

int	colors_red(float t)
{
	int	r;
	int	g;
	int	b;

	r = 9 * (1 - t) * t * t * t * 255;
	g = 16 * (1 - t) * (1 - t) * t * t * 255;
	b = 8 * (1 - t) * (1 - t) * (1 - t) * t * 255;
	return (b << 16);
}
int	colors_green(float t)
{
	int	r;
	int	g;
	int	b;

	r = 9 * (1 - t) * t * t * t * 255;
	g = 16 * (1 - t) * (1 - t) * t * t * 255;
	b = 8 * (1 - t) * (1 - t) * (1 - t) * t * 255;
	return (b << 8);
}

int	colors_wtf(float t)
{
	int	r;
	int	g;
	int	b;

	r = 9 * (1 - t) * t * t * t * 255;
	g = 16 * (1 - t) * (1 - t) * t * t * 255;
	b = 8 * (1 - t) * (1 - t) * (1 - t) * t * 255;
	return (r + g + b << 4);
}

int	fractol_formula(t_mlx_data *data)
{
	double	ind;
	double	real;

	ind = 0;
	while (ind++ < 100)
	{
		real = (data->n.z_real * data->n.z_real) - (data->n.z_i * data->n.z_i) + data->n.c_real;
		data->n.z_i = (data->n.z_real * data->n.z_i * 2) + data->n.c_i;
		data->n.z_real = real;
		if ((data->n.z_real * data->n.z_real) + (data->n.z_i * data->n.z_i) > 100)
		{
			if (data->color == XK_1)
				return ((ind / 100) * 16777216);
			else if (data->color == XK_2)
				return ((1 - (ind / 100)) * 16777216);
			else if (data->color == XK_3)
				return ((ind / 100) * 255);
			else if (data->color == XK_4)
				return ((int)(((ind / 100)) * 255) << 4);
			else if (data->color == XK_5)
				return ((int)(((ind / 100)) * 255) << 12);
			else if (data->color == XK_6)
				return (colors_wtf((ind / 100)));
		}
	}
	return (0);
}

// int	fractol_formula(double z_real, double z_i, double c_real, double c_i)
// {
	// long double	ind;
	// double		real;
// 
	// ind = 0;
	// while (ind++ < 100)
	// {
		// real = (z_real * z_real) - (z_i * z_i) + c_real;
		// z_i = (z_real * z_i * 2) + c_i;
		// z_real = real;
		// if ((z_real * z_real) + (z_i * z_i) > 4)
			// return (((ind / 100)) * 16777215);
	// }
	// return (0);
// }

void	restart_data(t_mlx_data *data, int ac, char **av)
{
	data->av = av;
	data->x_mult = 2.65;
	data->y_mult =  2.5;
	data->y_cords = 1.25;
	data->color = XK_1;
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
			data->n.z_real = ((x * data->x_mult / w)) - data->x_cords;
			data->n.z_i = data->y_cords - ((y * data->y_mult) / h);
			data->n.c_real = data->real;
			data->n.c_i = data->i;
			my_put_pixel(&data->img, x, y, fractol_formula(data));
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
	while (++y < h)
	{
		x = -1;
		while (++x < w)
		{
			data->n.z_real = 0;
			data->n.z_i = 0;
			data->n.c_real = ((x * data->x_mult / w)) - data->x_cords;
			data->n.c_i = data->y_cords - ((y * data->y_mult) / h);
			my_put_pixel(&data->img, x, y, fractol_formula(data));
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
	{
		data->n.z_real = ((x * data->x_mult / w)) - data->x_cords;
		data->n.z_i = data->y_cords - ((y * data->y_mult) / h);
		data->n.c_real = data->real;
		data->n.c_i = data->i;
		return (fractol_formula(data));
	}
	else
	{
		data->n.z_real = 0;
		data->n.z_i = 0;
		data->n.c_real = ((x * data->x_mult / w)) - data->x_cords;
		data->n.c_i = data->y_cords - ((y * data->y_mult) / h);
		return (fractol_formula(data));
	}
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
		restart_data(data, data->ac, data->av);
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
	if (keysym > XK_0 && keysym <= XK_6)
	{
		data->color = keysym;
		Julia_or_Mandelbrot(data);
	}
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


int	second_Julia_set(t_mlx_data *data, float r, float i)
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
			data->n.z_real = ((x * data->x_mult / w)) - 1.325;
			data->n.z_i = data->y_cords - ((y * data->y_mult) / h);
			data->n.c_real = r;
			data->n.c_i = i;
			my_put_pixel(&data->img2, x, y, fractol_formula(data));
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr2, data->img2.img_ptr, 0 , 0);
	return (0);
}

void	data_set(t_mlx_data *data, float rx, float ry)
{
	data->x_mult = 2.65;
	data->y_mult =  2.5;
	data->y_cords = 1.25;
	data->real = rx;
	data->i = ry;
	data->flag = 1;
	data->x_cords = 1.325;
}

void	my_put_pixel_lines(t_image *img, int x, int y)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->pixel_ptr)) = 16777215;
}

void	draw_line_aux(t_mlx_data *data, t_comp v, double a, double b)
{
	double	x;
	double	y;

	x = v.r_min - 1;
	while (++x < v.r_max && x < HIGHT - 1 && x > 0)
	{
		y = a * x + b;
		my_put_pixel_lines(&data->img, x, y);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0 , 0);
}

void	draw_line(t_mlx_data *data, t_comp v, double a, double b)
{
	double	x;
	double	y;

	y = v.i_min - 1;
	while (++y < v.i_max)
	{
		x = (y - b) / a;
		my_put_pixel_lines(&data->img, x, y);
	}
	draw_line_aux(data, v, a, b);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0 , 0);
}

int check_color(t_image *img, float x ,float y)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	return (*((unsigned int *)(offset + img->pixel_ptr)) != 0);
}

int	get_formula(t_comp z1, t_comp z2, t_mlx_data *data, int ind)
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
	if (z1.i < z2.i)
	{
		v.i_min = z1.i;
		v.i_max = z2.i;
	}
	else
	{
		v.i_max = z1.i;
		v.i_min = z2.i;
	}
	if (z1.real > z2.real)
	{
		v.r_max = z1.real;
		v.r_min = z2.real;
	}
	else
	{
		v.r_max = z2.real;
		v.r_min = z1.real;
	}
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
		if (get_formula(z1, z2, data, ind))
			return ;
		z1.real = z2.real;
		z1.i = z2.i;
	}
}

int	mouse_hook(int keysym, int x, int y, t_mlx_data *data)
{
	float	rx;
	float	ry;

	rx = x;
	ry = y;
	if (keysym == 1 && data->flag == 0)
	{
		if (data->win_ptr2 == NULL)
			data->win_ptr2 = mlx_new_window(data->mlx_ptr, WIDTH, HIGHT, "Julia_set");
		data->lr = (rx * data->x_mult / WIDTH) - data->x_cords;
		data->li = data->y_cords - ((ry * data->y_mult) / HIGHT);
		printf("%f %f\n", data->lr, data->li);
		second_Julia_set(data, (rx * data->x_mult / WIDTH) - data->x_cords, data->y_cords - ((ry * data->y_mult) / HIGHT));
	}
	if (keysym == 2)
		Julia_or_Mandelbrot(data);
	if (keysym == 2  && !check_color(&data->img, rx, ry))
		draw_orbit(data, (((rx - 94)* data->x_mult / WIDTH) - data->x_cords) / 1.124, data->y_cords - ((ry * data->y_mult) / HIGHT));
	if (keysym == 3 && data->flag == 0 && data->win_ptr2)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr2);
		data->win_ptr2 = NULL;
		data_set(data, data->lr, data->li);
		Julia_set(data);
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

	restart_data(&data, ac, av);
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
	data.img2.img_ptr = mlx_new_image(data.mlx_ptr, WIDTH, HIGHT);
	data.img2.pixel_ptr = mlx_get_data_addr
	(data.img2.img_ptr, &data.img2.bpp, &data.img2.line_len, &data.img2.endian);

	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, key_hook, &data);
	mlx_hook(data.win_ptr, ButtonPress, ButtonPressMask, mouse_hook, &data);
	Julia_or_Mandelbrot(&data);
	mlx_loop(data.mlx_ptr);
}

