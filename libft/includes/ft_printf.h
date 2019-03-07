/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dieu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 21:48:56 by tle-dieu          #+#    #+#             */
/*   Updated: 2019/03/07 15:31:51 by tle-dieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define BS_PRINTF 8192

# include <stdarg.h>
# include <inttypes.h>
# include <wchar.h>

typedef struct		s_print
{
	char			str[BS_PRINTF + 1];
	int				i;
	int				fd;
	int				error;
	int				total;

}					t_print;

typedef struct		s_flag
{
	int				plus;
	int				space;
	int				order;
	int				width;
	int				prec;
	int				minus;
	int				hashtag;
	int				zero;
	int				llf;
	int				l;
	int				h;
	int				j;
	int				z;
}					t_flag;

/*
** ------------------GENERAL-------------------
*/

int					ft_printf(char const *format, ...) __attribute__
((format(printf,1,2)));
int					ft_dprintf(int fd, char const *format, ...);
intmax_t			get_signed(va_list args, t_flag *flags);
uintmax_t			get_unsigned(va_list args, t_flag *flags);
int					base_len(uintmax_t nb, int base);
char				*atoi_jr(char *format, int *nb);

/*
** --------------------FLAG--------------------
*/

int					get_flags(va_list args, t_flag *flags, char **format);
int					init_flags(t_flag *flags);

/*
** --------------------CONV--------------------
*/

void				c_conv(t_print *buff, t_flag *flags, int c);
void				s_conv(t_print *buff, t_flag *flags, char *s);
void				p_conv(t_print *buff, t_flag *flags, uintmax_t nb);
void				di_conv(t_print *buff, t_flag *flags, intmax_t nb);
void				oux_conv(t_print *buff, t_flag *flags,
		uintmax_t nb, char *base);
void				f_conv(va_list args, t_print *buff,
		t_flag *flags, char conv);
void				lc_conv(t_print *buff, t_flag *flags,
		char **format, wint_t c);
void				ls_conv(t_print *buff, t_flag *flags,
		char **format, wchar_t *s);

/*
** --------------------BUFF--------------------
*/

void				empty_buff(t_print *buff);
void				field_in_buff(t_print *buff, int width, char zero);
void				color_in_buff(t_print *buff, char *color);

/*
** --------------------FTOA--------------------
*/

typedef struct		s_bint
{
	char			digit;
	struct s_bint	*next;
}					t_bint;

typedef struct		s_float
{
	char			mantissa[65];
	unsigned		exp;
	int				sign;
	int				size;
	t_bint			*intpart;
	t_bint			*floatpart;
}					t_float;

void				get_fbinary(t_float *f, unsigned char *c);
void				get_lfbinary(t_float *f, unsigned char *c);
t_bint				*get_intpart(char *mantissa, int size, int exp);
t_bint				*get_floatpart(char *mantissa, int size, int exp);
t_bint				*init_bint(char digit);
t_bint				*ret_intpart(t_bint *nb);
t_bint				*ret_floatpart(t_bint *nb);
t_bint				*add_bin_exp(t_bint *nb, t_bint *bin_exp);
t_bint				*double_bin_exp(t_bint *bin_exp);
t_bint				*divide_bin_exp(t_bint *bin_exp);
t_bint				*apply_prec(t_bint *floatpart, t_bint *intpart, int prec);
int					bint_len(t_bint *lst);
void				free_bint(t_bint **lst);
int					special_case(char *mantissa);
char				*get_specialf(int sign, int inf, char conv);

/*
** -------------------COLORS-------------------
*/

char				*get_style(char *color);
char				*dec_color(char *color, char *rgb);
char				*hex_color(char *s, char *rgb);
char				*get_bg(char *col, char *seq);

#endif
