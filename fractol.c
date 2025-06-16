/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlima-so <jlima-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:17:36 by jlima-so          #+#    #+#             */
/*   Updated: 2025/06/16 16:09:32 by jlima-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

void	restart_data(t_mlx_data *data, int ac, char **av)
{
	data->av = av;
	data->x_mult = 2.65;
	data->y_mult = 2.5;
	data->y_cords = 1.25;
	if (av != NULL)
		data->col = XK_1;
	data->sc = 150;
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

void	my_cpy_pixel_vert(t_image *img, int x, int y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->pixel_ptr)) = \
	*((unsigned int *)(offset + img->pixel_ptr + (img->line_len * color)));
}

int	go_func(t_mlx_data *data, double x, double y)
{
	double	w;
	double	h;

	w = WIDTH;
	h = HIGHT;
	if (data->flag)
	{
		data->n.z_r = ((x * data->x_mult / w)) - data->x_cords;
		data->n.z_i = data->y_cords - ((y * data->y_mult) / h);
		data->n.c_r = data->real;
		data->n.c_i = data->i;
		return (fractol_formula(data));
	}
	else
	{
		data->n.z_r = 0;
		data->n.z_i = 0;
		data->n.c_r = ((x * data->x_mult / w)) - data->x_cords;
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
	*((unsigned int *)(offset + img->pixel_ptr)) = \
		*((unsigned int *)(offset + img->pixel_ptr + ((img->bpp / 8) * color)));
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
		julia_set(data);
	else
		mandelbrot(data);
}

void	julia_or_mandelbrot(t_mlx_data *data)
{
	if (data->flag)
		julia_set(data);
	else
		mandelbrot(data);
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

void	movin_around(int key, t_mlx_data *data)
{
	if (key == XK_Down)
		go_up(data, 10);
	if (key == XK_Up)
		go_down(data, 10);
	if (key == XK_Right)
		go_left(data, 10);
	if (key == XK_Left)
		go_right(data, 10);
	if (key == XK_KP_Add)
		zoom(data, 1);
	if (key == XK_KP_Subtract)
		zoom(data, -1);
}

int	key_hook(int key, t_mlx_data *data)
{
	if (key == XK_Escape)
		exit_func(data);
	if (key == XK_space)
		restart_data(data, data->ac, NULL);
	if (key == XK_space)
		julia_or_mandelbrot(data);
	movin_around(key, data);
	if (key > XK_0 && key <= XK_7)
		color_code(key, data);
	if (key == XK_KP_Multiply)
		data->sc += 50;
	if (key == XK_KP_Divide && data->sc > 50)
		data->sc -= 50;
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->img.img_ptr, 0, 0);
	return (0);
}

void	mouse_zoom(t_mlx_data *data, int x, int y, int flag)
{
	float	rx;
	float	ry;

	rx = x;
	ry = y;
	data->x_cords += flag * ((data->x_mult / 10) * (rx / WIDTH) / 1.124);
	data->y_cords += flag * (data->y_mult / 10) * (ry / HIGHT);
	data->x_mult += flag * (data->x_mult / 10);
	data->y_mult += flag * (data->y_mult / 10);
	if (data->flag)
		julia_set(data);
	else
		mandelbrot(data);
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

void	my_put_pixel_lines(t_image *img, int x, int y)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->pixel_ptr)) = 16777215;
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
	x = v.r_min - 1;
	while (++x < v.r_max && x < HIGHT - 1 && x > 0)
	{
		y = a * x + b;
		my_put_pixel_lines(&data->img, x, y);
	}
	mlx_put_image_to_window
	(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
}

int	check_color(t_image *img, float x, float y)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	return (*((unsigned int *)(offset + img->pixel_ptr)) != 0);
}

int	get_formula(t_comp z1, t_comp z2, t_mlx_data *data)
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

void	mouse_hook_aux(int key, int x, int y, t_mlx_data *data)
{
	if (key == 3 && data->flag == 0 && data->win_ptr2)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr2);
		data->win_ptr2 = NULL;
		data_set(data, data->lr, data->li);
		julia_set(data);
	}
	if (key == 4)
		mouse_zoom(data, x, y, -1);
	if (key == 5)
		mouse_zoom(data, x, y, 1);
}

int	mouse_hook(int key, int x, int y, t_mlx_data *data)
{
	float	rx;
	float	ry;

	rx = x;
	ry = y;
	if (key == 1 && data->flag == 0)
	{
		if (data->win_ptr2 == NULL)
			data->win_ptr2 = \
				mlx_new_window(data->mlx_ptr, WIDTH, HIGHT, "julia_set");
		data->lr = (((rx - 94) * data->x_mult / WIDTH) - data->x_cords) / 1.124;
		data->li = data->y_cords - ((ry * data->y_mult) / HIGHT);
		second_julia_set(data,
			(((rx - 94) * data->x_mult / WIDTH) - data->x_cords)
			/ 1.124, data->y_cords - ((ry * data->y_mult) / HIGHT));
	}
	if (key == 2)
		julia_or_mandelbrot(data);
	if (key == 2 && !check_color(&data->img, rx, ry) && data->x_mult == 2.65)
		draw_orbit(data, (((rx - 94) * data->x_mult / WIDTH) - data->x_cords)
			/ 1.124, data->y_cords - ((ry * data->y_mult) / HIGHT));
	mouse_hook_aux(key, x, y, data);
	return (0);
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

int	main(int ac, char **av)
{
	t_mlx_data	data;

	restart_data(&data, ac, av);
	init_fractol(&data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, key_hook, &data);
	mlx_hook(data.win_ptr, ButtonPress, ButtonPressMask, mouse_hook, &data);
	julia_or_mandelbrot(&data);
	mlx_loop(data.mlx_ptr);
}
