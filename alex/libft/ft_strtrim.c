/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:02:09 by algultse          #+#    #+#             */
/*   Updated: 2023/11/17 16:56:37 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_char_to_remove(char const *s1, char const *set)
{
	int		j;
	int		i;
	size_t	size_s1;

	i = 0;
	j = 0;
	while (s1[i] && ft_strchr(set, s1[i++]))
		j++;
	size_s1 = ft_strlen(s1) - 1;
	while (size_s1 > 0 && ft_strchr(set, s1[size_s1--]))
		j++;
	if (size_s1 == 0 && ft_strchr(set, s1[size_s1]))
		j++;
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		i;
	int		j;
	int		len_res;

	if (!s1)
		return (NULL);
	j = count_char_to_remove(s1, set);
	len_res = (int)ft_strlen(s1) - j;
	if (len_res <= 0)
		return (ft_strdup(""));
	res = malloc(sizeof(char) * (len_res + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (s1[i] && j < len_res)
		res[j++] = s1[i++];
	res[j] = '\0';
	return (res);
}

/*
#include <stdio.h>
int main()
{
	printf ("ft_strtrim: [%s]\n", ft_strtrim("saltuttas", "sat"));
	printf ("count_char_to_remove: [%d]\n", count_char_to_remove("salutas", "sat"));
	return (0);
}
*/