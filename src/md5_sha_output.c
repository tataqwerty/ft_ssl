#include <ft_ssl.h>

static void	output_router(t_md5_sha_data *data, char *cmd_name)
{
	if (data->flags.q)
		ft_printf("%s\n", data->hashed);
	else if (data->flags.p)
		ft_printf("%s\n", data->hashed);
	else if (data->flags.r)
	{
		if (data->flags.s)
			ft_printf("%s \"%s\"\n", data->hashed, data->name);
		else if (data->flags.file)
			ft_printf("%s %s\n", data->hashed, data->name);
		else
			ft_printf("%s\n", data->hashed);
	}
	else
	{
		if (data->flags.s)
			ft_printf("%s (\"%s\") %s\n", cmd_name, data->name, data->hashed);
		else if (data->flags.file)
			ft_printf("%s (%s) %s\n", cmd_name, data->name, data->hashed);
		else
			ft_printf("%s\n", data->hashed);
	}
}

static void	clean_data(t_md5_sha_data *data)
{
	data->flags.s = 0;
	data->flags.file = 0;
	data->flags.p = 0;
	data->name = NULL;
	ft_strdel(&data->input);
	ft_strdel(&data->hashed);
	data->size = 0;
}

void		md5_sha_output(t_command *command)
{
	t_md5_sha_data	*data;
	char			*cmd_name;

	cmd_name = ft_strtoupper(command->name);
	(!cmd_name) ? ft_error("Error with malloc") : 0;
	data = (t_md5_sha_data *)command->data;
	data->hashed = command->hash(data->input);
	output_router(data, cmd_name);
	clean_data(data);
	ft_strdel(&cmd_name);
}
