#include <iostream>
#include <math.h>
#include <bits/stdc++.h> 
#define SIZE 10000000
#define STEP 25000
using namespace std;
float arr[SIZE];
float steps[SIZE/STEP];
float arr_val=0.2345f;
float abs_error(float val1,float val2){
	return abs(val2-val1);
}
float rel_error(float val1,float val2){
	return (abs_error(val1,val2)/val2)*100.0f;
}
void set_arr_val(float val){
	arr_val=val;
	for(int i=0;i<SIZE;i++){
		arr[i]=arr_val;
	}
}
// 1.1
float iter_sum(bool step){
	float res=0.0f;
	for(int i=0;i<SIZE;i++){
		res+=arr[i];
		if(step && i%STEP==0 && i!=0){
			steps[i/STEP]=rel_error(res,i*arr_val);
		}
	}
	return res;
}
// 1.4
float rec_sum(int left,int right){
	if(left==right){
		return arr[left];
	}
	return rec_sum(left,(left+right)/2)+rec_sum((left+right)/2+1,right);
}
float kahan_summation(){
	float sum=0.0f;
	float err=0.0f;
	for(int i=0;i<SIZE;i++){
		float y=arr[i]-err;
		float tmp=sum+y;
		err=(tmp-sum)-y;
		sum=tmp;
	}
	return sum;
}
int main(){
	cout<<"zadanie 1.2"<<endl;
	set_arr_val(0.2345f);
	float s=iter_sum(false);
	cout<<"blad bezwzgledny "<<abs_error(2345000.0f,s)<<endl;
	cout<<"blad wzgledny "<<rel_error(s,2345000.0f)<<endl;
	cout<<"###########################"<<endl;
	cout<<"zadanie 1.5"<<endl;
	float s1=rec_sum(0,SIZE-1);
	cout<<"s1= "<<s1<<endl;
	cout<<"blad bezwzgledny "<<abs_error(2345000.0f,s1)<<endl;
	cout<<"blad wzgledny "<<rel_error(s1,2345000.0f)<<endl;
	cout<<"###########################"<<endl;
	cout<<"zadanie 1.6"<<endl;
	time_t start,end;
	time(&start);
	iter_sum(false);
	time(&end);
	cout<<"sumowanie iteracyjne ,t="<<fixed<<double(end-start)<<setprecision(3)<<endl;
	time(&start);
	rec_sum(0,SIZE-1);
	time(&end);
	cout<<"sumowanie rekurencyjne, t="<<fixed<<double(end-start)<<setprecision(3)<<endl;
	cout<<"############################"<<endl;
	cout<<"zadanie 1.7"<<endl;
	set_arr_val(0.23f);
	s1=rec_sum(0,SIZE-1);
	cout<<"blad bezwzgledny "<<abs_error(arr_val*SIZE,s1)<<endl;
	cout<<"blad wzgledny "<<rel_error(s1,arr_val*SIZE)<<endl;
	cout<<"###########################"<<endl;
	cout<<"2.1"<<endl;
	set_arr_val(0.3f);
	s1=kahan_summation();
	cout<<"blad bezwzgledny "<<abs_error(arr_val*SIZE,s1)<<endl;
	cout<<"blad wzgledny "<<rel_error(s1,arr_val*SIZE)<<endl;
}