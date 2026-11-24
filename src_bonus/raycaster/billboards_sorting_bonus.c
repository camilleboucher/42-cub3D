/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   billboards_sorting_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 19:58:30 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/20 19:58:30 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	swap_players(int *pl_a, int *pl_b, double *dist_a, double *dist_b)
{
	int		pl_temp;
	double	dist_temp;

	if (*dist_a < *dist_b)
	{
		pl_temp = *pl_b;
		*pl_b = *pl_a;
		*pl_a = pl_temp;
		dist_temp = *dist_b;
		*dist_b = *dist_a;
		*dist_a = dist_temp;
	}
}

void	quick_players_sort(double dists[4], int players[4], int player_count)
{
	int	i;
	int	j;

	i = player_count;
	j = 0;
	while (i)
	{
		i--;
		j = 0;
		while (j < i)
		{
			swap_players(&players[j], &players[j + 1], &dists[j], &dists[j
				+ 1]);
			j++;
		}
	}
}
