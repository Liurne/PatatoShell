int	clear_env(char **env, int nb_v)
{
	int	i;

	i = 0;
	while((nb_v == -1 && env[i]) || (nb_v != -1 && i < nb_v))
	{
		free(env[i]);
		i++;
	}
	free(env);
}
char	**create_env(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	while(envp[i])
		i++;
	new_env = (char **)ft_calloc(i, sizeof(char *))
	if (!new_env)
		return (NULL);
	i = 0;
	while(envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if(!new_env[i])
			return(clear_env(new_env, i), NULL);
		i++;
	}
	return (new_env);
}

char	*get_env_var(char *var)
{
	int		i;
	char	*tmp;

	i = -1;
	while (g_envv[++i])
	{
		tmp = ft_strjoin(var, '=');
		if (ft_strstartswith(g_envv[i], tmp))
		{
			free(tmp);
			return (ft_strchr(g_envv[i], '=') + 1);
		}
		free(tmp);
	}
	return (NULL);
}

char	**add_var_env(char *line, char **env)
{
	int		i;
	char	**new_env;
	
	i = 0;
	while(env[i])
		i++;
	new_env = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	
	
	return ();
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_dprintf("%s\n", env[i]);
		i++;
	}
}