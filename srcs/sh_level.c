/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_level.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 13:18:58 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/17 19:36:13 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_value(int i, char *var, char *value)
{
	char *str;

	if (!(str = (char*)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	ft_bzero(str, i + 2);
	ft_strcat(str, var);
	ft_strcat(str, "=");
	ft_strcat(str, value);
	return (str);
}

void	reduc_shlvl(t_env **env, char *s)
{
	int		i;
	t_env	*tmp;
	char	*c;

	if (seak(s) == 0)
		return ;
	tmp = find_node(env, "SHLVL", NULL);
	if (!tmp)
		return ;
	i = ft_atoi(tmp->value);
	i--;
	c = ft_itoa(i);
	addvalue(&tmp, c);
	free(c);
}

void	ft_shlvl(t_env **env)
{
	int		i;
	t_env	*tmp;
	char	*c;

	tmp = find_node(env, "SHLVL", NULL);
	if (!tmp)
		return ;
	i = ft_atoi(tmp->value) + 1;
	c = ft_itoa(i);
	addvalue(&tmp, c);
	free(c);
}

char	**sh_lvl(t_env **lst, char *s)
{
	int		i;
	int		j;
	char	**newenv;
	t_env	*tmp;

	j = 0;
	i = countnode(*lst);
	if (!(newenv = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	tmp = *lst;
	if (seak(s) == 1)
		ft_shlvl(lst);
	while (tmp)
	{
		i = ft_strlen(tmp->var) + ft_strlen(tmp->value);
		newenv[j] = var_value(i, tmp->var, tmp->value);
		tmp = tmp->next;
		j++;
	}
	newenv[j] = NULL;
	return (newenv);
}
