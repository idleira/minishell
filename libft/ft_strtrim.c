/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:31:05 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/05/23 15:15:44 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* copy portion of src string to dst */
static char	*copy(char const *s1, char	*str, size_t len, size_t start)
{
	size_t	i;

	i = 0;
	while (i < len)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}

/* remove leading and trailing whitespace from string */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*str;
	size_t	start;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	if (!*s1)
		return (ft_strdup(""));
	len = ft_strlen((char *)s1) - 1;
	while (ft_strchr(set, s1[start]))
	{
		if (s1[start] == '\0')
			return (ft_strdup(""));
		start++;
	}
	while (ft_strchr(set, s1[len]))
		len--;
	len = len - start + 1;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	return (copy(s1, str, len, start));
}

// int main()
// {
//     const char *s1 = "   bo  njou r   ";
//     const char *set = " ";

//     char *result = ft_strtrim(s1, set);

//     printf("Original string: \"%s\"\n", s1);
//     printf("Trimmed string: \"%s\"\n", result);

//     return 0;
// }