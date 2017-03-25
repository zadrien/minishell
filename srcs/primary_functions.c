/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primary_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 18:22:43 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/17 19:33:49 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_equal(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == '=')
			return (1);
	return (0);
}

int		countnode(t_env *env)
{
	int		i;

	i = 0;
	if (!env)
		return (i);
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

int		find_path(t_env *lst)
{
	lst = find_node(&lst, "PATH", NULL);
	if (!lst)
		return (0);
	return (1);
}

int		test(char *s)
{
	if (check_equal(s) == 1)
		return (1);
	return (0);
}

t_env	*find_node(t_env **env, char *var, char *value)
{
	t_env	*tmp;

	tmp = *env;
	if (var != NULL)
		while (tmp && ft_strcmp(tmp->var, var) != 0)
			tmp = tmp->next;
	else
		while (tmp && ft_strcmp(tmp->value, value) != 0)
			tmp = tmp->next;
	return (tmp);
}
