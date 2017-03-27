/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_finder1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 18:36:17 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/27 13:40:13 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_dir(char *s)
{
	int		i;
	char	*str;

	str = NULL;
	i = ft_strlen(s);
	if (s[i - 1] == '/')
		str = ft_strdup(s);
	else
		str = ft_strjoin(s, "/");
	return (str);
}

char	*create_path(char *env, char *cmd)
{
	int		i;
	char	*str;

	i = ft_strlen(env) + ft_strlen(cmd);
	if (!(str = (char*)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	ft_bzero(str, i + 2);
	ft_strcat(str, env);
	i = ft_strlen(env);
	if (env[i - 1] != '/')
		ft_strcat(str, "/");
	ft_strcat(str, cmd);
	return (str);
}

char	*ft_findbinary(char **env, char *cmd)
{
	int		i;
	char	*bin;
	DIR		*dir;

	i = -1;
	while (env[++i])
		if ((dir = opendir(env[i])))
		{
			if (ft_checkbin(dir, cmd) == 1)
			{
				bin = create_path(env[i], cmd);
				closedir(dir);
				return (bin);
			}
			closedir(dir);
		}
	return (NULL);
}
