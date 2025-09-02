# Finals in arithmetic

## 题目描述

Vitya is studying in the third grade. During the last math lesson all the pupils wrote on arithmetic quiz. Vitya is a clever boy, so he managed to finish all the tasks pretty fast and Oksana Fillipovna gave him a new one, that is much harder.

Let's denote a flip operation of an integer as follows: number is considered in decimal notation and then reverted. If there are any leading zeroes afterwards, they are thrown away. For example, if we flip $ 123 $ the result is the integer $ 321 $ , but flipping $ 130 $ we obtain $ 31 $ , and by flipping $ 31 $ we come to $ 13 $ .

Oksana Fillipovna picked some number $ a $ without leading zeroes, and flipped it to get number $ a_{r} $ . Then she summed $ a $ and $ a_{r} $ , and told Vitya the resulting value $ n $ . His goal is to find any valid $ a $ .

As Oksana Fillipovna picked some small integers as $ a $ and $ a_{r} $ , Vitya managed to find the answer pretty fast and became interested in finding some general algorithm to deal with this problem. Now, he wants you to write the program that for given $ n $ finds any $ a $ without leading zeroes, such that $ a+a_{r}=n $ or determine that such $ a $ doesn't exist.

## 说明/提示

In the first sample $ 4=2+2 $ , $ a=2 $ is the only possibility.

In the second sample $ 11=10+1 $ , $ a=10 $ — the only valid solution. Note, that $ a=01 $ is incorrect, because $ a $ can't have leading zeroes.

It's easy to check that there is no suitable $ a $ in the third sample.

In the fourth sample $ 33=30+3=12+21 $ , so there are three possibilities for $ a $ : $ a=30 $ , $ a=12 $ , $ a=21 $ . Any of these is considered to be correct answer.

## 样例 #1

### 输入

```
4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
11
```

### 输出

```
10
```

## 样例 #3

### 输入

```
5
```

### 输出

```
0
```

## 样例 #4

### 输入

```
33
```

### 输出

```
21
```

# 题解

## 作者：chrhaa (赞：1)

# Finals in arithmetic

题意等价于找一个序列 $a$ 使得 $a+ar=n$。

首先将序列 $a$ 反转再加上原序列相当于有不考虑进位的答案序列 $b$ 满足 $b_i=a_i+a_{n-i+1}$。

因为 $0 \le a_i \le 9$，所以进位的最大值是1。那么考虑从中间同时往两边填数，记录填数的是否产生进位以及是否需要最后一位的进位，记录状态的可行性和可行转移点即可。

细节有点多，包括看最高位是不是0以及考虑序列 $a$ 长度可不可以比 $n$ 小1。

```
#include<stdio.h>
const int N=100005,B=10;

char s[N],t[N];
int m,g1[N][2][2],g2[N][2][2];
bool f[N][2][2];

bool solve(int n,int k){
	int i,j,k0,k1;
	m=(n+1)/2;
	
	for(i=0;i<=n;i++)
	for(k0=0;k0<2;k0++)
	for(k1=0;k1<2;k1++)
		f[i][k0][k1]=g1[i][k0][k1]=g2[i][k0][k1]=0;
	
	if(n&1){
		for(i=0;i<19;i+=2) if(s[m]==i%B){
			f[m][i/B][0]=true;
			g1[m][i/B][0]=i;
		}else if(s[m]==(i+1)%B){
			f[m][(i+1)/B][1]=true;
			g1[m][(i+1)/B][1]=i;
		}
	}else{
		for(i=0;i<19;i++)
		if(s[m]==i%B&&s[m+1]==(i+i/B)%B){
			f[m][(i+i/B)/B][0]=true;
			g1[m][(i+i/B)/B][0]=i;
		}else if(s[m]==(i+1)%B&&s[m+1]==(i+(i+1)/B)%B){
			f[m][(i+(i+1)/B)/B][1]=true;
			g1[m][(i+(i+1)/B)/B][1]=i;
		}
	}
	
	for(i=m-1;i>0;i--) for(j=0;j<19;j++){
		k0=j/B;
		k1=(j+1)/B;
		
		if(s[i]==j%B&&s[n-i+1]==j%B&&f[i+1][0][k0]){
			f[i][k0][0]=true;
			g1[i][k0][0]=j;
			g2[i][k0][0]=k0;
		}if(s[i]==j%B&&s[n-i+1]==(j+1)%B&&f[i+1][1][k0]){
			f[i][k1][0]=true;
			g1[i][k1][0]=j;
			g2[i][k1][0]=2|k0;
		}if(s[i]==(j+1)%B&&s[n-i+1]==j%B&&f[i+1][0][k1]){
			f[i][k0][1]=true;
			g1[i][k0][1]=j;
			g2[i][k0][1]=k1;
		}if(s[i]==(j+1)%B&&s[n-i+1]==(j+1)%B&&f[i+1][1][k1]){
			f[i][k1][1]=true;
			g1[i][k1][1]=j;
			g2[i][k1][1]=2|k1;
		}
	}
	
	if(!f[1][k][0]) return false;
	
	for(i=1,k0=k,k1=0;i<=m;i++){
		t[i]=(g1[i][k0][k1]+1)/2+48;
		t[n-i+1]=g1[i][k0][k1]/2+48;
		
		j=k0;
		k0=g2[i][j][k1]>>1;
		k1=g2[i][j][k1]&1;
	}
	
	return t[1]!=48;
}

signed main(){
	int i,n=0;
	scanf("%s",s+1);
	
	for(i=1;s[i];i++) n++,s[i]^=48;
	for(i=1;i<=n-i;i++){
		char c=s[i];
		s[i]=s[n-i+1];
		s[n-i+1]=c;
	}
	
	if(solve(n,0)){
		printf("%s\n",t+1);
		return 0;
	}
	
	if(s[n]==1&&solve(n-1,1))
		printf("%s\n",t+1);
	else puts("0");
	
	return 0;
}
```

---

## 作者：Little_Cart (赞：0)

考虑直接暴力从两边向中间枚举，如果两边的数一样则可以直接可以将左半边赋值为该数，右边赋值为 $0$。

如果不一样则考虑左半边是否为右半边的数减一，只有这一种可能合法，则打一个 tag 维护进位，否则不成立。

如果进位后左右两边数字相等，则需要一个 tag 来记录需要给下一个右边的数减一（因为要提供进位），然后每次开始时直接处理即可，如果会减为 $0$ 则从下一位借 $1$ 即可。

进位后对于 $0$ 和 $9$ 需要进行特殊判断，这个时候直接将左值赋值为 $9$，右值赋值为 $0$，打上进位 tag 即可。

最后由于进位 tag 可能没有归 $0$，或者因为某些原因出现了数字 $10$，这会导致答案不正确，所以需要扫一遍 check 来判断是否合法。

当开头数字为 $1$ 时，需要额外判断可不可以通过两个比他少 $1$ 位的数字转过来，这个仿照上文处理方式再做一遍即可。

具体实现和具体细节可以参考我的 $293$ 行代码。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
#define fi first
#define se second
#define mkp make_pair
const int N=300024;
int t,n,m,l,r;
string tp,rs,s,a,e,b,ra;
bool check(){
	int cur=0;
	ra=a;
	reverse(ra.begin(),ra.end());
	for(int i=n;i>0;i--){
		cur+=ra[i]+a[i]-'0'-'0';
		if(a[i]>'9'||a[i]<'0') return 0;
		if(((char)((cur%10)+'0'))==s[i]){
			cur/=10;
		}
		else{
			return 0;
		}
	}
	return 1;
}
bool check1(){
	int cur=0;
	ra=a;
	reverse(ra.begin(),ra.end());
	for(int i=n;i>1;i--){
		cur+=ra[i-1]+a[i]-'0'-'0';
		if(a[i]>'9'||a[i]<'0') return 0;
		if(((char)((cur%10)+'0'))==s[i]){
			cur/=10;
		}
		else{
			return 0;
		}
	}
	return 1;
}
bool check2(){
	int cur=0;
	ra=a;
	reverse(ra.begin(),ra.end());
	for(int i=n;i>1;i--){
		cur+=ra[i-1]+a[i]-'0'-'0';
		if(((char)((cur%10)+'0'))==s[i]){
			cur/=10;
		}
		else{
			return 0;
		}
	}
	return 1;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>tp;
	s=" "+tp;
	rs=s;
	n=tp.size();
	l=1;
	r=n;
	for(int i=0;i<=n+1;i++){
		a+="0";
	}
	bool flag=1;
	int flag2=0;
	while(l<=r){
		if(flag2&2){
			s[r]--;
			if(s[r]<'0'){
				s[r]='9';
				flag2+=2;
			}
			flag2-=2;
		}
		if(flag2&1){
			if(l==r){
				if((s[r]-'0')%2==0){
					a[l]=(s[r]-'0'+10)/2+'0';
					l++;
					r--;
					flag2=0;
				}
				else{
					flag=0;
					break;
				}
			}
			else if(s[l]==s[r]){
				a[l]=(s[r]-'0'+10)/2+'0';
				a[r]=a[l]+(s[r]-'0'+10)%2;
				l++;
				r--;
				flag2=2;
			}
			else if(s[l]-1==s[r]){
				a[l]=(s[r]-'0'+10)/2+'0';
				a[r]=a[l]+(s[r]-'0'+10)%2;
				flag2=3;
				l++;
				r--;
			}
			else if(s[l]=='0'&&s[r]=='9'){
				a[l]='9';
				a[r]='0';
				flag2|=1;
				l++;
				r--;
			}
			else{
				flag=0;
				break;
			}
		}
		else{
			if(l==r){
				if((s[r]-'0')%2==0){
					a[l]=(s[r]-'0')/2+'0';
					l++;
					r--;
				}
				else{
					flag=0;
					break;
				}
			}
			else if(s[l]==s[r]){
				a[l]=s[l];
				a[r]='0';
				l++;
				r--;
			}
			else if(s[l]-1==s[r]&&(s[l]!='1'||l!=1)){
				a[l]=s[l]-1;
				a[r]='0';
				flag2=1;
				l++;
				r--;
			}
			else if(s[l]=='0'&&s[r]=='9'){
				a[l]='9';
				a[r]='0';
				flag2=1;
				l++;
				r--;
			}
			else{
				flag=0;
				break;
			}
		}
	}
	s=rs;
	if(check()){
		flag2=0;
	}
	else{
		flag=0;
	}
	if(!flag||flag2){
		s=rs;
		if(s[1]=='1'&&s!=" 1"){
			l=2;
			r=n;
			flag=1;
			flag2=1;
			while(l<=r){
				//cout<<l<<" "<<r<<" "<<flag2<<"\n";
				if(flag2&2){
					s[r]--;
					if(s[r]<'0'){
						s[r]='9';
						flag2+=2;
					}
					flag2-=2;
				}
				if(flag2&1){
					if(l==r){
						if((s[r]-'0')%2==0){
							a[l]=(s[r]-'0'+10)/2+'0';
							l++;
							r--;
							flag2=0;
						}
						else{
							flag=0;
							break;
						}
					}
					else if(s[l]==s[r]){
						a[l]=(s[r]-'0'+10)/2+'0';
						a[r]=a[l]+(s[r]-'0'+10)%2;
						l++;
						r--;
						flag2=2;
					}
					else if(s[l]-1==s[r]){
						a[l]=(s[r]-'0'+10)/2+'0';
						a[r]=a[l]+(s[r]-'0'+10)%2;
						flag2=3;
						l++;
						r--;
					}
					else if(s[l]=='0'&&s[r]=='9'){
						a[l]='9';
						a[r]='0';
						flag2|=1;
						l++;
						r--;
					}
					else{
						flag=0;
						break;
					}
				}
				else{
					if(l==r){
						if((s[r]-'0')%2==0){
							a[l]=(s[r]-'0')/2+'0';
							l++;
							r--;
						}
						else{
							flag=0;
							break;
						}
					}
					else if(s[l]==s[r]){
						a[l]=s[l];
						a[r]='0';
						l++;
						r--;
					}
					else if(s[l]-1==s[r]&&(s[l]!='1'||l!=1)){
						a[l]=s[l]-1;
						a[r]='0';
						flag2=1;
						l++;
						r--;
					}
					else if(s[l]=='0'&&s[r]=='9'){
						a[l]='9';
						a[r]='0';
						flag2=1;
						l++;
						r--;
					}
					else{
						flag=0;
						break;
					}
				}
			}
			s=rs;
			//if(s[2]=='3'&&s[3]=='9'&&s[4]=='3'){
			//	for(int i=n;i>n-14;i--){
			//		cout<<s[i];
			//	}
			//	cout<<"\n";
			//	cout<<flag<<" "<<l<<" "<<r<<" "<<s[l]<<" "<<s[r]<<" "<<flag2<<"\n";
			//}
			if(check1()){
				flag2=0;
			}
			else{
				flag=0;
			}
			if(!flag||flag2){
				cout<<"0";
			}
			else{
				for(int i=2;i<=n;i++){
					cout<<a[i];
				}
			}
		}
		else{
			cout<<"0";
		}	
	}
	else{
		for(int i=1;i<=n;i++){
			cout<<a[i];
		}
	}
	return 0;
}
```

---

