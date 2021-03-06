/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 12:41:34 by gdannay           #+#    #+#             */
/*   Updated: 2017/11/14 16:56:31 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void	ft_strclr(char *s)
{
	size_t	size;
	size_t	i;

	i = 0;
	if (s != NULL)
	{
		size = ft_strlen(s);
		while (i < size)
		{
			s[i] = '\0';
			i++;
		}
	}
}
