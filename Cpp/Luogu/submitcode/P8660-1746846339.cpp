#include <bits/stdc++.h>
using namespace std;
struct node{int l,r;};
int n,m,l,r=2e5,x,y;
vector<node> a,b;
inline bool pd(const int& k) noexcept{
	b=a;
	bool bo;
	int l,s=0;
	while (1){
		bo=true;
		l=b.size();
		for (int i=0;i<l;i++)
			if (b[i].l>=s){
				if (b[i].l-s<=k){
					s+=b[i].r-b[i].l;
					b.erase(b.begin()+i--);
					bo=false;
					break;
				}
			}
			else{
				if (s-b[i].l<=k) s+=b[i].r-b[i].l;
				  else s=max(s,b[i].r+k);
				b.erase(b.begin()+i--);
				bo=false;
				break;
			}
		if (bo||b.empty()) break;
	}
	return s>=2e4;
}
int main(){
	cin>>n;
	while (n--){
		scanf("%d%d",&x,&y);
		a.push_back(node{x<<1,y<<1});
	}
	sort(a.begin(),a.end(),[](const node& a,const node& b){return a.r<b.r||(a.l<b.l&&a.r==b.r);});
	while (l<r) pd(m=l+r>>1)?(r=m):(l=m+1);
	cout<<l/2.0<<"\n";
	return 0;
}