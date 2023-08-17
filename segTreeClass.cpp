#include<iostream>
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);init_code();
#include<bits/stdc++.h>
#define ll long long 
#define vi vector<int>
#define read(x) int x;cin>>x;
using namespace std;
void init_code(){
	#ifndef ONLINE_JUDGE
	freopen("inputf.txt","r",stdin);
	freopen("outputf.txt","w",stdout);
	#endif
}
class sgtree{
public: 
	vi arr;
	sgtree(int size){
		arr.resize(4*size +1 );
	}
	void build(vi& a ,int low,int high, int ind){
	if (low == high){
		arr[ind] = a[low];
		//cout <<ind<<"->"<<arr[ind]<<" ";
		return;
	}
	int mid = low+ (high-low)/2;
	build(a,low,mid,2*ind+1);
	build(a,mid+1,high,2*ind+2);
	arr[ind] = min(arr[2*ind+1],arr[2*ind+2]);
	//cout <<ind<<"->"<<arr[ind]<<" ";
	}
	int findMin(int l,int r,int low,int high,int ind){
		//cout << "l->"<<l<<",r->"<<r<<",low->"<<low<<",high->"<<high<<",ind->"<<ind<<endl;
		// No overlap
		if (l>high or r<low)return INT_MAX;
		//Complete overlap
		else if (low >= l and high <= r)return arr[ind];
		//partial overlap
		int mid = low + (high-low)/2;
		int left = findMin(l,r,low,mid,2*ind+1);
		int right = findMin(l,r,mid+1,high,2*ind+2);

		return min(left,right);
	}
	void update(int low,int high, int index,int val, int ind){
		if (index == low and low == high){
			arr[ind] = val;return;
		}
		int mid = low + (high-low)/2;
		if (index <= mid)update(low,mid,index,val,2*ind+1);
		if (index > mid)update(mid+1,high,index,val,2*ind+2);
		arr[ind] = min(arr[2*ind+1],arr[2*ind+2]);
	}
};
int main(){
	fast;
	read(m);vi a(m);for (int i=0;i<m;i++)cin>>a[i];
	read(n);vi b(n);for (int i=0;i<n;i++)cin>>b[i];
	sgtree sg1(m);
	sgtree sg2(n);
	sg1.build(a,0,m-1,0);
	sg2.build(b,0,n-1,0);
	read(p);
	for (int i=0;i<p;i++){
		read(opt);
		if (opt == 1){
			int l1,l2,r1,r2;cin>>l1>>r1>>l2>>r2;
			cout <<sg1.findMin(l1,r1,0,m-1,0)<<" ";
			cout <<sg2.findMin(l2,r2,0,n-1,0)<<endl;
		}
		//index is taken as input 
		else if (opt == 2){
			int x,index,val;cin>>x>>index>>val;
			if (x == 1)sg1.update(0,m-1,index,val,0);
			else if (x == 2 )sg2.update(0,n-1,index,val,0);
		}
	}
	return 0;
}