/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 09:19:32 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/17 19:19:15 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_path(t_env **env, char *var, char *value, char *value2)
{
	(*env)->var = ft_strdup(var);
	(*env)->value = ft_strjoin(value, value2);
}

void	init_cpy(t_env **env, char *var, char *value)
{
	(*env)->var = ft_strdup(var);
	(*env)->value = ft_strdup(value);
}

t_env	*init_nenv(void)
{
	t_env	*p;
	t_env	*tmp;

	if (!(p = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	tmp = p;
	init_path(&tmp, "PATH", PATH, PATH2);
	if (!(tmp->next = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	tmp = tmp->next;
	init_cpy(&tmp, "USER", "zadrien");
	if (!(tmp->next = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	tmp = tmp->next;
	init_cpy(&tmp, "LOGNAME", "zadrien");
	if (!(tmp->next = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	tmp = tmp->next;
	init_cpy(&tmp, "SHLVL", "1");
	tmp->next = NULL;
	return (p);
}

t_env	*init_env(char **env, t_env **lst)
{
	int		i;
	t_env	*tmp;
	char	**tab;

	i = -1;
	if (countab(env) == 0)
		return (init_nenv());
	if (!(*lst = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	tmp = *lst;
	while (env[++i] && (tab = ft_strsplit(env[i], '=')))
	{
		addcontentlst(&tmp, tab);
		if (env[i + 1])
		{
			if (!(tmp->next = (t_env*)malloc(sizeof(t_env))))
				return (NULL);
			tmp = tmp->next;
		}
		ft_freetab(tab);
	}
	tmp->next = NULL;
	return (*lst);
}
