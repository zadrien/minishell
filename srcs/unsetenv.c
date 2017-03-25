/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 18:39:03 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/17 17:59:33 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freenode(t_env *node)
{
	ft_strdel(&node->var);
	if (node->value)
		ft_strdel(&node->value);
	free(node);
}

void	deletevar(t_env **tmp, t_env *prev)
{
	prev->next = (*tmp)->next;
	freenode(*tmp);
}

void	deletefirstnode(t_env **lst)
{
	t_env	*tmp;

	tmp = *lst;
	*lst = tmp->next;
	freenode(tmp);
}

void	deletevarenv(t_env **lst, char *var)
{
	t_env	*prev;
	t_env	*tmp;

	prev = NULL;
	tmp = (*lst);
	while (tmp && ft_strcmp(tmp->var, var) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		ft_errormsg("env: ", var, ": Variable not set.");
	else if (!prev)
		deletefirstnode(lst);
	else if (tmp && ft_strcmp(tmp->var, var) == 0)
		deletevar(&tmp, prev);
}

void	ft_unsetenv(t_env **env, char **tab)
{
	int		i;

	if ((i = countab(tab)) == 1)
		deletevarenv(env, tab[0]);
	else if (i == 0)
		ft_errormsg(NULL, NULL, "unsetenv: Too few arguments.");
	else if (i > 1)
		ft_errormsg(NULL, NULL, "unsetenv: Too many arguments.");
}
