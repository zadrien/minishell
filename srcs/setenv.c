/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 20:30:05 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/17 19:30:30 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	addcontentlst(t_env **lst, char **tab)
{
	(*lst)->var = ft_strdup(tab[0]);
	if (tab[1])
		(*lst)->value = ft_strdup(tab[1]);
	else
		(*lst)->value = ft_strdup("");
}

void	addvalue(t_env **env, char *str)
{
	ft_strdel(&(*env)->value);
	if (str)
		(*env)->value = ft_strdup(str);
	else
		(*env)->value = ft_strdup("");
}

void	implentvar(t_env **lst, char **tab)
{
	t_env	*tmp;
	t_env	*node;

	tmp = (*lst);
	while (tmp->next)
	{
		if (ft_strcmp(tmp->var, tab[0]) == 0)
		{
			addvalue(&tmp, tab[1]);
			return ;
		}
		tmp = tmp->next;
	}
	if (ft_strcmp(tmp->var, tab[0]) == 0)
		addvalue(&tmp, tab[1]);
	else if ((node = (t_env*)malloc(sizeof(t_env))))
	{
		node->next = NULL;
		addcontentlst(&node, tab);
		tmp->next = node;
	}
}

void	create_nlst(t_env **env, char **tab)
{
	t_env *node;

	if (!(node = (t_env*)malloc(sizeof(t_env))))
		return ;
	node->next = NULL;
	addcontentlst(&node, tab);
	*env = node;
}

void	ft_setenv(t_env **env, char **tab, char **path)
{
	int		i;

	if ((i = countab(tab)) > 2)
		ft_errormsg(NULL, NULL, "setenv: Too many arguments.");
	else if (i == 0)
		printenv(*env, NULL, path);
	else
	{
		if (verif_format(tab) == 1)
		{
			ft_errormsg("usage: ", "setenv: ", "[Variable] [Value]");
			return (ft_errormsg(NULL, "setenv: ",
				"Variable name must contain alphanumeric characters."));
		}
		if (countnode(*env) == 0)
			create_nlst(env, tab);
		else
			implentvar(env, tab);
	}
}
