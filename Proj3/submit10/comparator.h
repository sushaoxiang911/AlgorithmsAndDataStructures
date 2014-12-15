#ifndef COMPARATOR_H
#define	COMPARATOR_H

static struct compclass1
{
	bool operator ()(entry* data1,entry* data2)
	{
		if(data1->timestamp != data2->timestamp)
		{
			return data1->timestamp < data2->timestamp;
		}
		else
		{
			if(data1->categorylower!=data2->categorylower)
			{
				return data1->categorylower < data2->categorylower;
			}
			else
			{
				if(data1->id<data2->id)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
	}
}comp_time;


static struct compclass2
{
	bool operator()(entry* data1,entry* data2)
	{
		if(data1->categorylower != data2->categorylower)
		{
			return data1->categorylower < data2->categorylower;
		}
		else
		{
			if(data1->timestamp != data2->timestamp)
			{
				return data1->timestamp < data2->timestamp;
			}
			else
			{
				if(data1->id<data2->id)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
	}
}comp_category;



static struct compclass3
{
	bool operator()(entry* data1 , entry* data2)
	{
		return (data1->id==data2->id);
	}
}entryptrunique;


static struct compclass4
{
	bool operator()(entry* data1 , entry* data2)
	{
		return (data1->id<data2->id);
	}
}entryptreq;



#endif
