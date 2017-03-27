/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 16:45:22 by zadrien           #+#    #+#             */
/*   Updated: 2017/03/27 12:20:57 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include "../libft/libft.h"
# define PATH_MAX 2048
# define PATH "/Users/zadrien/.brew/bin:/usr/bin:/bin:/usr/sbin:"
# define PATH2 "/sbin:/usr/local/bin:/usr/local/munki:/Library/TeX/texbin"

typedef struct		s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}					t_env;

/*
*******************
** BUILTIN : CD **
*****************
*/
void				ft_access(char *s);
void				init_pwd(t_env **env);
void				cd_home(t_env **env);
void				change_directory(t_env **env, char **tab);
void				ft_cd(char **tab, t_env **env);
void				old_pwd(t_env **env, char *s);
void				met_hode(t_env **env, char *home);
void				go_oldpwd(t_env **env);

/*
***********************
** BUILTIN : SETENV **
*********************
*/
void				ft_setenv(t_env **env, char **tab, char **path);
void				create_nlst(t_env **env, char **tab);
void				implentvar(t_env **lst, char **tab);
void				addvalue(t_env **env, char *str);
void				addcontentlst(t_env **lst, char **tab);
/*
*************************
** BUILTIN : UNSETENV **
***********************
*/
void				freenode(t_env *node);
void				deletevar(t_env **tmp, t_env *prev);
void				deletefirstnode(t_env **lst);
void				deletevarenv(t_env **lst, char *var);
void				ft_unsetenv(t_env **env, char **tab);

/*
********************
** BUILTIN : ENV **
******************
*/
void				exec_env_cmd(t_env **env, char **tab, char **path);
void				printenv(t_env *env, char **tab, char **path);
void				env(t_env **env, char **tab, char **path);

/*
*********************
** BUILTIN : ECHO **
*******************
*/
void				echo(t_env **env, char **tab);
void				print_echo(char **tab, int index, char *s);
void				ft_echo(t_env **env, char **tab);
char				*ft_stockbuff(char *str, char *buf);

/*
************************
** PRIMARY FUNCTIONS **
*********************
*/
int					check_equal(char *s);
int					countnode(t_env *env);
int					find_path(t_env *lst);
int					test(char *s);
t_env				*find_node(t_env **env, char *var, char *value);
int					verif_format(char **tab);
int					ft_checkbin(DIR *dir, char *cmd);
int					find_bin(char *path, char *file);
int					seak(char *s);
int					dollar(t_env **env, char **tab);

/*
********************
** BINARY FINDER **
******************
*/
char				*new_dir(char *s);
char				*create_path(char *env, char *cmd);
char				*ft_findbinary(char **env, char *cmd);
char				*path_1case(char *cmd);
void				exec_1case(t_env **env, char **tab);
void				binary_finder(t_env **env, char **cmd, char **path);
void				init_cpy(t_env **env, char *var, char *value);
void				time_4_magic(char *cmd, char **tab, char **env);
char				**ft_getpath(t_env *env, char **path);
char				**ft_output(t_env **env, char **path);
int					ft_checkbuiltin(char *str);
void				ft_freetab(char **tab);
t_env				*init_env(char **env, t_env **lst);
void				init_cmd(t_env **lst, char **tab, char **path);
void				exec_cmd(char **tab, char **path, t_env **env);
int					countab(char **tab);
char				**sh_lvl(t_env **lst, char *s);
void				ft_shlvl(t_env **env);
void				reduc_shlvl(t_env **env, char *s);
void				ft_exit(t_env **lst, char **tab, char **path);

#endif
