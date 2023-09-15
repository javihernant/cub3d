#include "libft.h"
#include "mlxutils.h"

void	ft_draw_line_low(int x1, int y1, int x2, int y2, int color, t_mlxconf *conf)
{
	int		d;

	int difx = x2 - x1;
	int dify = y2 - y1;
	int		yi = 1;
	if (dify < 0)
	{
		yi = -1;
		dify = -dify;
	}
	d = (2 * dify) - difx;
	int tmpy1 = y1;
	int tmpx1 = x1;
	while (tmpx1 <= x2)
	{
		ft_pixel_put(tmpx1, tmpy1, color, conf);
		if (d > 0)
		{
			tmpy1 += yi;
			d += (2 * (dify - difx));
		}
		else
			d += 2 * dify;
		tmpx1++;
	}
}

void	ft_draw_line_high(int x1, int y1, int x2, int y2, int color, t_mlxconf *conf)
{
	int		d;

	int difx = x2 - x1;
	int dify = y2 - y1;
	int		xi = 1;
	// int inc = 1;
	if (difx < 0)
	{
		xi = -1;
		difx = -difx;
	}
	d = (2 * difx) - dify;
	int tmpy1 = y1;
	int tmpx1 = x1;
	while (tmpy1 <= y2)
	{
		ft_pixel_put(tmpx1, tmpy1, color, conf);
		if (d > 0)
		{
			tmpx1 += xi;
			d += (2 * (difx - dify));
		}
		else
			d += 2 * difx;
		tmpy1++;
	}
}

void ft_draw_line(int x1, int y1, int x2, int y2, int color, t_mlxconf *conf)
{
	if (abs(y2 - y1) < abs(x2 - x1))
	{
		if (x1 < x2)
			ft_draw_line_low(x1, y1, x2, y2, color, conf);
		else
			ft_draw_line_low(x2, y2, x1, y1, color, conf);
	}
	else
	{
		if (y1 < y2)
			ft_draw_line_high(x1, y1, x2, y2, color, conf);
		else
			ft_draw_line_high(x2, y2, x1, y1, color, conf);
	}
}

