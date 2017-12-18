/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:06:04 by gdannay           #+#    #+#             */
/*   Updated: 2017/12/13 19:32:17 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <inttypes.h>
# include <wchar.h>
# include "libft.h"

# define BINA "01"
# define DECI "0123456789"
# define HEXAMIN "0123456789abcdef"
# define HEXAMAJ "0123456789ABCDEF"
# define OCTA "01234567"
# define BUFF_SIZE 4096

typedef struct			s_flag
{
	int					minus;
	int					plus;
	int					space;
	int					zero;
	int					hash;
	int					width;
	int					precision;
	int					length;
	char				type;
	int					inttype;
	int					intdisplay;
	long long			nb;
	unsigned long long	unb;
	char				*st;
	wchar_t				*wst;
	struct s_flag		*next;
}						t_flag;

typedef struct			s_type
{
	char				type;
	int					conv;
	int					display;
}						t_type;

int						ft_printf(char *str, ...);
t_flag					*create_flag(void);
int						length_nbr(int n);
t_flag					*check_carac(char *str, int *i);
void					fill_wp(t_flag *tmp, va_list va);
void					check_width(char *str, int *i, t_flag *new, int *ret);
void					check_wp(char *str, int *i, t_flag *new);
int						display(char *str, t_flag *flag);
char					*ltoa_base(t_flag *tmp, char *base);
char					*utoa_base(t_flag *tmp, char *base);
char					*chartostr(long long c);
int						display_flag(char *new, t_flag *tmp, char *buff);
int						manage_nb(t_flag *tmp, char *buff);
int						manage_string(t_flag *tmpa, char *buff);
int						manage_char(t_flag *tmp, char *buff);
char					*ft_bchar(char c, size_t length);
int						display_precision(char *buff, t_flag *tmp, int index);
int						display_width(char *buff, t_flag *tmp, int index);
int						correction_sign(char *new, t_flag *tmp, int index);
int						manage_uni(t_flag *tmp, char *buff);
int						compute_rep(char *c);
int						manage_wstring(t_flag *tmp, char *buff);
int						size_hexa(long long n);
int						display_0(t_flag *tmp, char *c, char *buff);
int						compute_rep(char *c);
void					check_width(char *str, int *i, t_flag *new, int *ret);
void					check_wp(char *str, int *i, t_flag *new);
void					free_lst(t_flag **flag);
int						print_buff(char *buff);
int						manage_buff(char *buff, char *str, size_t length);
int						add_right(char *buff, char *str, int index, size_t length);
int						add_char_right(char *buff, char c, int index, size_t length);
int						add_char_left(char *buff, char c, int index, size_t length);

#endif
