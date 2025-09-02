# Beautiful IP Addresses

## 题目描述

The problem uses a simplified TCP/IP address model, please read the statement carefully.

An IP address is a 32-bit integer, represented as a group of four decimal 8-bit integers (without leading zeroes), separated by commas. For example, record 0.255.1.123 shows a correct IP address and records 0.256.1.123 and 0.255.1.01 do not. In the given problem an arbitrary group of four 8-bit integers is a correct IP address.

Our hero Polycarpus still works as a system administrator in some large corporation. He likes beautiful IP addresses. To check if some IP address is beautiful, he should do the following:

1. write out in a line four 8-bit numbers of the IP address, without the commas;
2. check if the resulting string is a palindrome.

Let us remind you that a palindrome is a string that reads the same from right to left and from left to right.

For example, IP addresses 12.102.20.121 and 0.3.14.130 are beautiful (as strings "1210220121" and "0314130" are palindromes), and IP addresses 1.20.20.1 and 100.4.4.1 are not.

Polycarpus wants to find all beautiful IP addresses that have the given set of digits. Each digit from the set must occur in the IP address at least once. IP address must not contain any other digits. Help him to cope with this difficult task.

## 样例 #1

### 输入

```
6
0 1 2 9 8 7
```

### 输出

```
6
78.190.209.187
79.180.208.197
87.190.209.178
89.170.207.198
97.180.208.179
98.170.207.189
```

## 样例 #2

### 输入

```
1
4
```

### 输出

```
16
4.4.4.4
4.4.4.44
4.4.44.4
4.4.44.44
4.44.4.4
4.44.4.44
4.44.44.4
4.44.44.44
44.4.4.4
44.4.4.44
44.4.44.4
44.4.44.44
44.44.4.4
44.44.4.44
44.44.44.4
44.44.44.44
```

# 题解

## 作者：jdsb (赞：4)

## 题目大意
给定N个整数，用它们来组成一个合法的回文IP地址，每个整数都要用到

## 分析

- 我们需要dfs暴力枚举前一半的数字，因为是回文，所以后一半就要满足回文性质，在枚举数字的时候有一个小技巧，用一个二进制数flag来存有哪些数字是要用的，在dfs的时候也用一个二进制数use来存当前已经用过哪些数字，如果到了到了最后发现use！=flag则违法，就要退出

- 将枚举出来的数字进行拆分，并进行判断，违法的情况有两种 1. 当前这组数的首位为0，且这组数不只有一位。 2. 这组数数字大于255或小于0。除此之外的合法IP地址我们都加入答案，最后输出即可。

## 代码(部分注释在代码中)
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,flag,tot;
bool check(string s,int l,int r)
{
	if(s[l]=='0')
	{
		if(r==l+1) return 1;
		return 0;
	}
	int x=0;
	for(int i=l;i<r;i++)
		x=(x<<3)+(x<<1)+(s[i]-'0');
	if(x>=0&&x<=255) return 1;
	return 0;
}
string ans[8888];
void solve(string s)
{
	int len=s.size();
	for(int i=1;i<=3;i++)
		for(int j=i+1;j<=i+3;j++)
			for(int k=j+1;k<=j+3;k++)
			{
				if(len-k>=1&&len-k<=3&&check(s,0,i)&&check(s,i,j)&&check(s,j,k)&&check(s,k,len))
				//如果最后一组数的位数不在1~3中说明不合法 
				ans[++tot]=s.substr(0,i)+"."+s.substr(i,j-i)+"."+s.substr(j,k-j)+"."+s.substr(k,len-k);
			}
}
//四项分别是当前枚举的位数，最大位数，当前使用数字的字符串，已使用的数字 
void dfs(int k,int maxk,string s,int use)
{
	if(k==maxk)
	{
		if(use==flag) solve(s);
		return;
	}
	if(k*2>maxk-1)
	{
		if(use!=flag) return;
		dfs(k+1,maxk,s+s[maxk-k-1],use);
		return;
	}
	for(int i=0;i<=9;i++)
		if(flag&(1<<i))
		//判断是否有i这个数字 
			dfs(k+1,maxk,s+char(i+'0'),use|(1<<i));
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		flag|=1<<x;
		//用二进制数存用哪些数 
	}
	if(n<=6)
	{
		for(int i=4;i<=12;i++)
			dfs(0,i,"",0);
	}
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++)
		cout<<ans[i]<<endl;
	return 0;
}
```




---

## 作者：HaneDaniko (赞：3)

比赛的时候打的这题，挺好的一道搜索。

题目让我们找到又合法又回文的 IP 地址。首先我们需要明白一点：既然是回文的，那么我们在枚举可能情况的时候就不需要把全部可能的 $12$ 位全部都填一遍，而是只找前面最多六位，然后按回文填后面。这样的话，搜索的时间开销才能降下来，我们加一个合法性检查才不会超时。

第一层搜索，我们枚举全部可能合法的回文数，然后进入第二层。在第二层里，我们需要枚举可能存在的三个分隔符的位置，然后检查我们构造出来的这个串是不是符合 IP 地址的格式。最后输出方案，那就全部塞进 vector 里，排个序就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
int a[11];//可以选择的决策
bool vis[11];int cnt;//用来判断是不是全都选了
vector<int> p;//存放回文数
vector<string> tres;//存放合法答案
bool check(vector<int> &r,int ri,int rj,int rk){
  //判断由r在ri,rj,rk位置后各断开一次是否合法
	int res=0;
	if(r[0]==0&&ri!=0) return false;//是否有前导0
	for(int i=0;i<=ri;++i){
		res=res*10+r[i];
	}
	if(res>255) return false;//是否超界
	res=0;
	if(r[ri+1]==0&&rj!=ri+1) return false;
	for(int i=ri+1;i<=rj;++i){
		res=res*10+r[i];
	}
	if(res>255) return false;
	res=0;
	if(r[rj+1]==0&&rk!=rj+1) return false;
	for(int i=rj+1;i<=rk;++i){
		res=res*10+r[i];
	}
	if(res>255) return false;
	res=0;
	if(r[rk+1]==0&&rk!=r.size()-2) return false;
	for(int i=rk+1;i<=r.size()-1;++i){
		res=res*10+r[i];
	}
	if(res>255) return false;
	string ress;//存放答案
	for(int i=0;i<=r.size()-1;++i){
		ress.push_back(r[i]+'0');
		if(ri==i||rj==i||rk==i){
			ress.push_back('.');
		}
	}
	tres.push_back(ress);
	return true;
}
int devide(bool isj){
  //第二层
	int ans=0;
	vector<int> r;
  //构造回文数
	for(int i:p){
		r.push_back(i);
	}
	if(!isj){
		r.push_back(p[p.size()-1]);
	}
	for(int i=p.size()-2;i>=0;--i){
		r.push_back(p[i]);
	}
  //尝试放置分隔符
	for(int i=0;i<=r.size()-2;++i){
		for(int j=i+1;j<=r.size()-2;++j){
			for(int k=j+1;k<=r.size()-2;++k){
				if(check(r,i,j,k)) ans++;
			}
		}
	}
	return ans;
}
void dfs(int len,int pla,int last){
  //第一层
	if(pla==(len+1)/2){
		if(cnt==n) ans+=devide(len&1);
		return;
	}
	for(int i=1;i<=n;++i){
		p.push_back(a[i]);
		if(!vis[i]){
			vis[i]=1;cnt++;
			dfs(len,pla+1,i);
			vis[i]=0;cnt--;
		}
		else{
			dfs(len,pla+1,i);
		}
		p.pop_back();
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
	}
	for(int len=4;len<=12;++len){
		dfs(len,0,1);
	}
	sort(tres.begin(),tres.end());
	cout<<ans<<endl;
	for(string i:tres){
		cout<<i<<endl;
	}
}
```

---

## 作者：MC小萌新 (赞：3)

### 题目分析
本题要求出所有美丽地址，由于 IP 地址的限制，导致可行的数量比较少，直接 dfs 枚举即可。

在枚举时，为提高程序效率，我们可以考虑只枚举序列的前一半，然后通过回文串的特点得到后一半，并判断它是否合法。之后再考虑向数列中加点。每次加点时，判断每一组数是否在 $ 0 $ ~ $ 255 $ 之间，如果不是，则无需继续往下枚举。

### 代码实现
在实现过程中，需要注意一些细节地方。主要有以下几点：

- 边界问题：在枚举点的位置的时候，要注意每一位不可以没有数字。
- 前导 $ 0 $ 问题：在返回每一组的值时，顺便判断这一组是否存在前导 $ 0 $ ，如果是，则不再继续计算。
- 放点问题：在放点时，要注意所放的点是在当前字符的前面还是后面，本题解的代码以放在后面的版本给出。
- 其他问题：判断是否合法时每次数组记得归 $ 0 $ 或直接定义在函数内部。

其他的就不必多说了，具体实现细节详见下方代码。
```cpp
#include<iostream>
using namespace std;
int n,a[11],res;
string s[1111100];
//返回这一组的值
int val(string s,int st,int e){
    int ans=0;
    bool state=0;
    for(int i=st;i<e;++i){
        if(s[i]!='0')
            state=1;
        if(s[i]=='0' && state==0 && i!=e-1)
            return 1e9;
        ans=ans*10+s[i]-'0';
    }
    return ans;
}
//向生成的数列中放'.'
void solve(string ans){
    int k=ans.size();
    for(int i=1;i<k-2;++i){
        if(val(ans,0,i)>255)
            continue;
        for(int j=i+1;j<k-1;++j){
            if(val(ans,i,j)>255)
                continue;
            for(int m=j+1;m<k;++m){
                if(val(ans,j,m)>255 || val(ans,m,k)>255)
                    continue;
                int cnt=0;
                ++res;
                for(int q=0;q<k;++q){
                    if(q==i || q==j || q==m){
                        s[res]+='.';
                        ++cnt;
                    }
                    s[res]+=ans[q];
                }
            }
        }
    }
}
//生成完整数字序列
void qwq(int d,int k,string ans){//一共d位，现有k位,要考虑的数列ans
    if(d%2){
        int cnt=k-2;
        for(int i=k;i<d;++i)
            ans+=ans[cnt--];
    }
    else{
        int cnt=k-1;
        for(int i=k;i<d;++i)
            ans+=ans[cnt--];
    }
    solve(ans);
}
bool ck(string s){//判断生成的是否合法。如果有没用到的数字即为不合法
    int b[100]={};
    for(int i=0;i<s.size();++i){
        b[s[i]-'0']=1;
    }
    for(int i=1;i<=n;++i)
        if(!b[a[i]])
            return 0;
    return 1;
}
//生成一半数字序列
void make(int d,int k,int now,string ans){//应有d位，一半有k位，当前枚举到第now位，枚举生成数列为ans
    if(now==k+1){
        if(ck(ans))
            qwq(d,k,ans);
        return ;
    }
    for(int i=1;i<=n;++i){
        make(d,k,now+1,ans+((char)(a[i]+'0')));
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    for(int k=4;k<=12;++k){//位数
        make(k,(k+1)/2,1,"");//只需枚举前一半
    }
    cout<<res<<endl;
    for(int i=1;i<=res;++i)
        cout<<s[i]<<endl;
    return 0;
}

```


---

## 作者：dzk_QwQ (赞：3)

### 题意

  定义一个合法的回文IP地址为 $Beautiful IP Address $ （回文地址就是去掉“.”后是个回文字符串的地址）， 给出 $n$ 个数字，求出所有可用这些数字组成的 $Beautiful Addresses$ 。（IP地址为一个 $32$  位的二进制数 ， 分成四组 $8$ 位的二进制整数（无前导$0$ ) .

  注：每个数都必须用到且只能使用这些数字。

### 分析

   首先，对于一个回文数，我们只需要知道它的前面一半即可。所以我们用dfs来暴力枚举前面一半的每种情况，然后对于我们所要使用的数字，我们用 $2$ 进制来存放这些数字 ， 然后对于每个枚举的数我们也用一个 $2$ 进制数来存储，表示我们使用过的数字，这样子当我们最后统计答案时，只需判断这两个数是否相等即可。

   其次，对于每个枚举出来的回文数都要满足一个性质： $IP$ 地址。所以说我们要判断将这些数字进行拆分，在每次拆分时，判断他是否合法， $1$ .每组数的首位都不能为 $0$ 除非这个数只有一位 .  $2$ .我们对于数字都要满足不大于 $255$  和 不小于$ 0 $ 。满足条件的都是合法的IP地址，具体实现看代码。

（因为是刚开始写题解，在楼下同机房大佬 $jdsb$ 的帮助下完成，思路类似，在这里对其感谢）。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n , a , MAX_num , cnt;
string ans[ 5010 ];
bool check( string s , int l , int r ){
	if( s[ l ] == '0' ){
	 if( r == l + 1 ) return 1;
	 return 0;
	}
	int x = 0 ;
	for( int i = l ; i < r ; i ++ )
	x = ( x << 3 ) + ( x << 1 ) + ( s[ i ] - '0' );
    if( x >= 0 && x <= 255 ) return 1;
    return 0; 
}
void work( string s ){
	int len = s.size( );
	for( int i = 1 ; i <= 3 ; i ++ ){
	 for( int j = i + 1 ; j <= i + 3 ; j ++ )
	  for( int k = j + 1 ; k <= j + 3 ; k ++ ){
	  	if( len - k >= 1 && len - k <= 3 && check( s , 0 , i )  && check( s , i , j ) && check( s , j , k ) && check( s , k ,len )){//每段IP地址是否合格 
	     ans[ ++cnt ] = s.substr( 0 , i ) + '.' + s.substr( i , j - i ) + '.' + s.substr( j , k - j  ) + '.' + s.substr( k , len - k );  
		} 
 	  }
	}
}
void dfs( int k , int MAXk , string s , int used ){
	if( k == MAXk ) {
		 if( used == MAX_num ) work( s );
		 return;
	}
	if( k * 2 > MAXk - 1 ){
		if( used != MAX_num ) return;
		dfs( k + 1 , MAXk , s + s[ MAXk - k - 1 ] , used );
		return;
	}
    for( int i = 0 ; i <= 9 ; i ++ ){
	 if( MAX_num & ( 1 << i ) )
	 dfs( k + 1 , MAXk , s + char( i + 48 )  , used | ( 1 << i ) );
	} 
}
int main( ){
	scanf("%d" , &n );
	for( int i = 1 ; i <= n ; i ++ ){
	 scanf("%d" , &a );
	 MAX_num |= ( 1 << a );
   }
   if( n <= 6 ){
   	 for( int i = 4 ; i <= 12 ; i++ )
   	  dfs( 0 , i , "" , 0 ); 
	}
	printf("%d\n" , cnt );
	for( int i = 1 ; i <= cnt ; i ++ ){
		 cout<< ans[ i ]<<endl;
	}
    return 0;
} 	
```



### 总结

 难度不大，代码理解读者自行理解，有问题可以评论，谢谢。

---

## 作者：a_123_a (赞：2)

### 思路1
此题其实不难~~但是十分麻烦~~，因为它是回文的，所以我们可以尝试使用 DFS 枚举前半段的回文串，然后判断其是否使用了规定的所有数字，然后枚举  IP  地址的三个分段的位置，就可以了。

### 过程1
具体来讲，我们可以搜索回文串长度为 $ 4 $ 到 $ 12 $ 的情况（因为每一位 IP 至少用 $ 1 $ 位数，至多用 $ 3 $ 位数），将需要用的数字利用位运算存储为一个 int 变量，在求解出回文串的过程中同时记录使用的数字，再在回文串构造完后进行比较，就能得到是否合法了。


值得注意的一点是，需要特殊处理 IP 全 $ 0 $ 的情况。

剩下的就看代码吧。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define intl long long
#define For(i,a,b) for(intl i=a;i<=b;i++)
intl n,a[15],need;
queue<string> ans;//存储所有的答案 
bool check(string s, intl l, intl r) {
	if(s[l] == '0') {
		if (r - l == 1) return 1;//对前导零与零进行判断 
		else return 0;
	}
	intl x = 0;
	For(i,l,r-1) x *= 10, x += s[i] - '0';
	return (x >= 0 && x <= 255);
}
void func(intl l, string s) {
	For(i,1,3) For(j,i+1,i+3) For(k,j+1,j+3) 
	if(l - k <= 3 && l - k >= 1) {//枚举分段 
		if(check(s, 0, i) && check(s, i, j) && check(s, j, k) && check(s, k, l)) {//检查每一个数是否合法 
			string x;
			For(t,0,i-1) x += s[t];x += '.';
			For(t,i,j-1) x += s[t];x += '.';
			For(t,j,k-1) x += s[t];x += '.';
			For(t,k,l-1) x += s[t];
			ans.push(x);//保存正确的答案 
		}
	}
	return ;
}
void dfs(intl l, intl pos, intl used, string s) {
	if (pos == l) {//回文串构造完成，进行存储 
		if (used == need) func(l, s);
		return ;
	}
	intl pos2=l-1-pos;
	if(pos2 < pos){//回文串前半段已经构造完成 
		if(need != used) return ;//查看数字是否全部使用 
		char c=s[pos2];
		dfs(l,pos+1,used,s+c);
	}
	else{
		For(i,0,9) {
			if(need & (1<<i)){//查看数字是否可用 
				char c='0'+i;
				dfs(l,pos+1,used|(1<<i),s+c);
			}
		}
	}
}
int main() {
	scanf("%lld",&n);
	For(i,1,n){
		scanf("%lld",&a[i]);
		need += (1 << a[i]);
	}
	if( n > 6 ){ //根据题意回文串最多只有12位，我们可以进行特判 
		printf("0\n");
		return 0;
	} 
	For(i,4,12) dfs(i,0,0,"");//枚举回文串长度 
	printf("%d\n",ans.size());
	while(!ans.empty()) {cout<<ans.front()<<"\n";ans.pop();}
	return 0;
}
```
只是第一种。
### 思路2
将每一个分段用一个 int 类型保存，检查它是否合法（全部由给定的数字组成），然后再将它们拼起来就可以了（代码依旧长）。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 305
#define intl long long
#define For(i,a,b) for(intl i=a;i<=b;i++)
#define deo(i,a,b) for(intl i=a;i>=b;i--)
intl n,aw[N<<2],ax[N<<2],ay[N<<2],az[N<<2],ka;
intl mask[N],kd[N],d[N][N],g[N],q[N];
bool b[N],good[N];
int main(){
	cin>>n;
	intl need=0;
	For(i,1,n) {
		intl a;cin>>a;
		need |= (1<<a);
		b[a] = 1;
	}
	if(n > 6) {printf("0");return 0;}
	intl kg=0;
	For(i,0,255) {
		good[i] = 1;
		intl x = i;
		mask[i] = kd[i] = 0;
		while(x){
			d[i][kd[i]++] = x%10;
			if(!b[x%10]) good[i] = 0;
			mask[i] |= (1<<(x%10));x/=10;
		}
		if(i == 0 && !b[0]) good[i]=0;
		if(i == 0){
			d[i][kd[i]++]=0;
			mask[i] |= (1<<0);
		}
		if(good[i]) g[kg++]=i;
	}
	intl ka = 0;
	For(w,0,255) if(good[w]) For(x,0,255) if(good[x]) For(y,0,255) if(good[y]){
		if((mask[y]|mask[x]|mask[w]) != need ) continue;
		For(z,0,255)
			if(good[z]){
				intl u=0;
				deo(i,kd[w]-1,0) q[u++]=d[w][i];
				deo(i,kd[x]-1,0) q[u++]=d[x][i];
				deo(i,kd[y]-1,0) q[u++]=d[y][i];
				deo(i,kd[z]-1,0) q[u++]=d[z][i];
				intl flag=1;
				For(i,0,u-i-2) 
					if(q[i] != q[u-i-1]){flag=0;break;}//判断是不是回文 
				if(flag){aw[++ka]=w;ax[ka]=x;ay[ka]=y;az[ka]=z;} //如果是的话就保存 
			}
	}
	printf("%lld\n",ka);
	for(intl i=1;i<=ka;i++)
		printf("%lld.%lld.%lld.%lld\n",aw[i],ax[i],ay[i],az[i]);//输出
	return 0;				
}
```

---

## 作者：GavinCayne (赞：2)

# 题目大意
输入数的个数 $n$，用**所有**给定的数组成一个地址（地址要求：每位不大于 $255$ 不小于 $0$，无前导零），满足地址去掉中间的点是一个回文数
## 整理一波思路
1. 既然要用**所有**的数，那么最短的回文数为左右各有 $n-1$ 个数，中间单独 $1$ 个数，长度为 $2n-1$，那只要 $n$ 超过 $6$，那么长度最小为 $13$，地址的 $4$ 位全是 $3$ 位数也满足不了，**直接舍去**。
1. 由于题目要找出每一个符合的地址，本题考虑用 **dfs**，需要 $2$ 个参数（~~不知道写题解的其他大佬是怎么弄出 $4$ 个的~~）一个为整个地址的长度 $l$，另一个为当前所在的位置 $t$。由于回文数的左右两边是颠倒的，**枚举前半段**即 $t\le(l+1)\div2$ 就能**直接推出后半段**。构造前半段只需要知道每一段的位数，然后所有可用的数试一遍存入每一位（别忘了回溯）。$t>(l+1)\div2$ 时先构造后一段，若当前为第 $i$ 位，则第 $l+1-i$ 位与它相同。最后特判数有没有全用上，利用 $4$ 个地址每一位上的数求出地址，判断在不在 $0$ 和 $255$ 之间。
1. 怎么得到总长度？怎么知道每个地址有几位？创建一个 $len$ 函数，两个参数 $p$ 和 $l$，$p$ 表示处理的是 $4$ 串地址中的那一串，$l$ 表示总长度，用个全局变量存每一串地址长就行。当 $p=5$ 就直接 dfs。
### 大家喜闻乐见的代码时间

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[15],s[10],use=0,ip[25],k=0;bool v[10];
//s代表每一个地址段有几位，ip代表每一位的数，k代表方案总数，v代表每个数有没有用 
int ans[100005][10];// ans用二维数组，第二位是第几个地址段 
void dfs(int l,int t)// 找合法地址,t是当前的位置 
{
	if(t>(l+1)/2)// 构造回文的前一半，推后一半 
	{
		if(use!=n)return;// 数没有用完
		for(int i=1;i<t;i++)ip[l+1-i]=ip[i];// 构造完回文 
		int cnt=0;// count计数
		int x[10]={0};// 每一段地址的数据
		for(int i=1;i<=4;i++)// 四段地址检验每段合法性 
		{	 
			for(int j=0;j<s[i];j++)// 枚举地址数组每一位 
			{
				cnt++;
				if(ip[cnt]==0&&s[i]>1&&j==0)return;// 删去前导零 
				x[i]=x[i]*10+ip[cnt];// 把地址数组合成一个数，类比字符串 
			}
			if(x[i]>255)return;// 合法性判断 
		}
		k++;//能构成 
		for(int i=1;i<=4;i++)ans[k][i]=x[i];// 方案成立，存好数组 
		return;
	}
	for(int i=1;i<=n;i++)
	{
		ip[t]=a[i];
		if(v[i])dfs(l,t+1);// 如果数用过 
		else{
			use++;v[i]=1;
			dfs(l,t+1);// 如果第一次用 
			use--;v[i]=0;// 回溯 
		}
	}
}
void len(int p,int l)// 搜总共四段的地址 
{
	if(p==5)// 超过四段，构成地址 
	{
		dfs(l,1);return;
	}
	for(int i=1;i<=3;i++)// 本段用几位数（最多3位）
	{
		s[p]=i;len(p+1,l+i);
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	if(n>6)// 特判 
	{
		cout<<0<<endl;return 0;
	} 
	len(1,0);// 开始dfs 
	cout<<k<<endl;// 输总数
	for(int i=1;i<=k;i++)// 输方案 
	{
		for(int j=1;j<=3;j++)cout<<ans[i][j]<<'.';//最后一段没有'.'单独输 
		cout<<ans[i][4]<<endl;
	}
	return 0;
}
```
完结撒花~（本蒟蒻第一次做题解，这也是本蒟的唯二AC的紫题之一。代码应该很好理解，长度适中，只有两个函数。~~看到其他出题解的大佬三四个函数两三层循环头都大~~ 如有疑问尽请指点~OwO）

---

## 作者：_ayaka_ (赞：1)

## 思路
此题其实不难，我们可以尝试使用 DFS 枚举前半段的回文串，然后判断其是否使用了规定的所有数字，再枚举 IP 地址的三个分段的位置，就可以了。

具体来说，我们可以搜索回文串长度为 $4$ 到 $12$ 的情况（因为每一位 IP 至少用 $1$ 位数，至多用 $3$ 位数），将需要用的数字利用位运算存储为一个 int 变量，在求解出回文串的过程中同时记录使用的数字，再在回文串构造完后进行比较，就能得到是否合法了。

值得注意的一点是，尽管不能存在有前导零的情况，但还需要特殊处理 IP 等于 $0$ 的情况。

其中具体的做法见代码。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, a[15], need;
queue<string> ans;//存储所有的答案 
bool check(string s, int l, int r) {
	if (s[l] == '0') {
		if (r - l == 1) return true;//对前导零与零进行判断 
		else return false;
	}
	int x = 0;
	for (int i = l; i < r; i++) x *= 10, x += s[i] - '0';
	return (x >= 0 && x <= 255);
}
void func(int l, string s) {
	for (int i = 1; i <= 3; i++) for (int j = i+1; j <= i+3; j++) for (int k = j+1; k <= j+3; k++) if (l-k<=3&&l - k >= 1) {//枚举分段 
					if (check(s, 0, i) && check(s, i, j) && check(s, j, k) && check(s, k, l)) {//检查每一个数是否合法 
						string x;
						for (int a = 0; a < i; a++) x += s[a];
						x += '.';
						for (int a = i; a < j; a++) x += s[a];
						x += '.';
						for (int a = j; a < k; a++) x += s[a];
						x += '.';
						for (int a = k; a < l; a++) x += s[a];
						ans.push(x);//保存正确的答案 
					}
				}
	return ;
}
void dfs(int l, int pos, int used, string s) {
	if (pos == l) {//回文串构造完成，进行存储 
		if (used == need) func(l, s);
		return ;
	}
	int pos2=l-1-pos;
	if(pos2<pos){//回文串前半段已经构造完成 
		if(need!=used) return ;//查看数字是否全部使用 
		char c=s[pos2];
		dfs(l,pos+1,used,s+c);
	}else{
		for(int i=0;i<=9;i++){
			if(need&(1<<i)){//查看数字是否可用 
				char c='0'+i;
				dfs(l,pos+1,used|(1<<i),s+c);
			}
		}
	}
}
signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		need += (1 << a[i]);
	}
	if(n>6){//根据题意回文串最多只有12位，我们可以进行特判 
		cout<<"0\n";
		return 0;
	} 
	for (int i = 4; i <= 12; i++) dfs(i, 0, 0, "");//枚举回文串长度 
	cout<<ans.size()<<"\n";
	while(!ans.empty()) cout<<ans.front()<<"\n",ans.pop();
	return 0;
}

```

---

## 作者：_zhaosihan_qwq_ (赞：0)

# 题解：CF292C Beautiful IP Addresses
## 翻译
题目给我们一些给定的数，让我们找出所有符合 IP 条件且回文的字符串。
## 思路
- 首先考虑数字越界，所有数字的值都不能超过 $255$，我们列举出条件后判断一下就行了。
- 然后就是前导 $0$，这里的前导 $0$ 必须提前判断，不能在最后判断，否则最后的字符串不是回文。
- 字符串的容器为 vector，不能使用 string，否则会 MLE。
- 时间复杂度 $O(nk+n)$，可以过。

本题较水，代码不给了。

---

## 作者：Epi4any (赞：0)

本文讲解优化暴力做法。

首先我们不难想到枚举所有可能的 ipv4 地址，但是太慢了，时间复杂度为 $O(2^{36})$。

然后我们来优化这个暴力。
- $0\sim 255$ 中有很多数并没有出现在给定的集合中，我们可以不用进行下一步循环。
- 我们枚举完前三个数时 ipv4 地址的有效数位必定过半，说明所有的数必须出现至少一次。

然后一些卡常优化。
- 判断所有数有没有用上可以使用位运算。
- 预处理所有数的数位，这样检查答案的时候不用再拆一次。

以上全部**预处理**解决。

[code](https://www.luogu.com.cn/record/163930388)

---

## 作者：Igallta (赞：0)

## 题目介绍

这道题我们读完题后看到题目给的条件：

IP 地址，且去掉分割的点以后的纯数字字符串是回文，那么就叫做美丽的 IP。

## 暴力方法

是不是听起来很简单，我先介绍一个大多数人都能想到的部分分做法：

枚举出所有 IP 的纯数字字符串，然后判断回文。

是回文那就考虑点的位置。

就是那么简单，但是我们来算一算最坏会运行多少次。

首先，我们要知道，IPv4 地址的每一位都是 $0$ ~ $255$。

那么一共就是 $266^4$ 种，通过计算器我们得知这个大小大概是 $5 \times 10^9$。

很明显，这种算法是无法通过的，那我们就要加以优化。

## 优化

我们想一下：既然我们都要判断回文了，为什么我们不直接构造一个回文呢？

那你可能要问了：“你说得那么简单，那怎么构造回文？而且，就算构造了，你怎么证明你这个算法就是对的？”

### 如何构造回文？

我们先一起想一想我们是怎么用双指针判断回文的。

是不是像这样一个指头一个指尾，然后同时向中间走？

![](https://cdn.luogu.com.cn/upload/image_hosting/pm16zh60.png)

那我们可不可以反过来，先填充绿色箭头，再填充浅灰色、深灰色、黑色？

最后我们把构造的回文存在一个 `vector` 变量里面，等会去分割点不就行了么？

哦对了，对于 IP 产生的纯数字字符串长度是 $8$ ~ $12$。我的做法会去判断奇偶，如果是奇数就先特殊地添加一位（绿色箭头），偶数则不用。

### 如何添加分割点？

我们在这里先写一个判断（check）来判断这个串是否是合法，判断的方法其实就只是把这个纯数字串转成数字，进行判断是否 $\geqslant 0$ 以及 $\leqslant 255$，方便我们后面进行分割。

我们想一想，我们已经求出了原数字串，已经规定了一共三个点。

那么我们为什么不可以切割出四个数字串，然后用三个点连接起来呢？

思路就是这样，模拟即可。

---

