#pragma once
//1//cehiakbcdikegfgjjdifhhglj
//1//aiheccbkekidgfgfidjjjlghh


void rin()
{
	while (1)
	{
		srand((unsigned)time(NULL));
		RandKind = rand() % KIND;
		if (buzhenout[RandKind][23] == 'l')
			buzhen = 1;
		else
			buzhen = 2;
		if (RandKind == 7)
			continue;
		else
			break;
	}
}