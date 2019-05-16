#include<stdio.h>

float temp(float q,float x, float k)
{
	float dT=q*x/k;
	return dT;
}

float equivalent(float k1,float k2,float x1,float x2,float q)
{
	float dT1 = temp(q,x1,k1);
	float dT2 = temp(q,x2,k2);
	float dT= dT1+dT2;
	return dT;
}

void main()
{
	float q=1000.0; // heat flux
	float x1=10.0,x2=20.0,x3=20.0; //length of materials
	float k1=205.0,k2=385.0,k3=50.2; //thermal heat conductivity
	int n=201; //number of nodes
	float L= x1+x2+x3; // total length

	float dx=L/(n-1); //distance between 2 consecutive nodes

	float t[n];
	float x[n]; //node co-ordinates as x
	int i;
	t[n-1]=25; // Boundary condition

	//finding node co-ordinates
	x[0]=0.0; //1st node
	for(i=1;i<n;i++)
	{
		x[i]=i*dx;
	}
	if(x[n-1]==L)
		printf("Nodes setup complete \n");
	else
		printf("Nodes setup ERROR \n");

	printf("The results are as follows:\n");
	float dT;

	for(i=n-2;i>=0;i--)
	{
		if(x[i]>=x1+x2)
			dT = temp(q,dx,k3);

		else if(x[i]>=x1 && x[i]<(x1+x2) && x[i+1]>(x1+x2))
			dT=equivalent(k3,k2,x[i+1]-(x1+x2),(x1+x2)-x[i],q);

		else if(x[i]>=x1 && x[i]<(x1+x2))
			dT = temp(q,dx,k2);

		else if(x[i]>=0 && x[i]<x1 && x[i+1]>x1)
			dT=equivalent(k2,k1,x[i+1]-x1,x1-x[i],q);

		else if(x[i]>=0 && x[i]<x1)
			dT = temp(q,dx,k1);

		t[i]=t[i+1]+dT;
	}

	FILE *data;
	data=fopen("data.dat","w");

	printf("NODE\tTEMPERATURE(celcius)\n");
	for(i=0;i<n;i++)
	{
	    fprintf(data,"%f\t%f\n",x[i],t[i]);
		printf("%f\t%f\n",x[i],t[i]);
	}
	fclose(data);
}
