/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enennige <enennige@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 13:46:41 by enennige          #+#    #+#             */
/*   Updated: 2018/06/07 12:07:52 by enennige         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The function ft_countwords() takes a string and a delimiter and counts the
** number of words between the delimiters.
*/

int	ft_countwords(const char *str, char delim)
{
	int in_word;
	int num_words;
	int i;

	in_word = 0;
	num_words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == delim)
		{
			i++;
			in_word = 0;
		}
		else
		{
			if (in_word == 0)
			{
				in_word = 1;
				num_words++;
			}
			i++;
		}
	}
	return (num_words);
}
