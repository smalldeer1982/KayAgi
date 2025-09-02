# T-shirts from Sponsor

## 题目描述

某著名比赛的知名赞助商决定给比赛的每个参赛者一件T恤作为礼物。

现在出现了一个问题：一方面，目前尚不清楚应该订购什么尺码的T恤，另一方面，他不想订购太多的T恤。经过大量的脑力训练和一些预估，赞助商订购了一定数量的尺寸为S，M，L，XL和XXL的T恤。T恤最终带来了好运，在比赛那天有一排参与者都想得到一件。

每个参赛者都以Ta期望的T恤尺码为特征（尺寸S，M，L，XL和XXL之一）。参与者一个接一个地拿到T恤。

如果还有适合的尺寸的T恤，那么Ta就会拿走它。否则，参赛者会选择尺寸尽可能接近最佳尺寸的T恤（相邻尺码之间的距离等于1）。如果有多种可供选择，参赛者将选择更大尺寸的T恤。例如，对于最佳大小为L的人，首选项列表如下所示：L，XL，M，XXL，S。

## 样例 #1

### 输入

```
1 0 2 0 1
3
XL
XXL
M
```

### 输出

```
XXL
L
L
```

# 题解

## 作者：Tune_ (赞：5)

还没有人发布题解？那本蒟蒻来一篇~

其实就是纯模拟，~~就是代码有点长~~。

按顺序判断要拿哪个号的衣服就好了，写上一堆if就搞定~

在以下代码中，有一种情况我注释详解~

————————————————————~~超长代码预警~~————————————————————

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int s,m,l,xl,xxl,k;
	cin>>s>>m>>l>>xl>>xxl>>k;
	string a;
	for(int i=1;i<=k;i++)
	{
		cin>>a;
		if(a=="S")
		{
			if(s)
			{
				cout<<"S"<<endl;
				s--;
			}
			else
			{
				if(m)
				{
					cout<<"M"<<endl;
					m--;
					continue;
				}
				if(l)
				{
					cout<<"L"<<endl;
					l--;
					continue;
				}
				if(xl)
				{
					cout<<"XL"<<endl;
					xl--;
					continue;
				}
				if(xxl)
				{
					cout<<"XXL"<<endl;
					xxl--;
					continue;
				}
			}
		}
		if(a=="M")
		{
			if(m)
			{
				cout<<"M"<<endl;
				m--;
			}
			else
			{
				if(l)
				{
					cout<<"L"<<endl;
					l--;
					continue;
				}
				if(s)
				{
					cout<<"S"<<endl;
					s--;
					continue;
				}
				if(xl)
				{
					cout<<"XL"<<endl;
					xl--;
					continue;
				}
				if(xxl)
				{
					cout<<"XXL"<<endl;
					xxl--;
					continue;
				}
			}
		}
		if(a=="L")//以L为例
		{
			if(l)//有刚好的
			{
				cout<<"L"<<endl;
				l--;
			}
			else
			{
				if(xl)//大一号
				{
					cout<<"XL"<<endl;
					xl--;
					continue;
				}
				if(m)//小一号
				{
					cout<<"M"<<endl;
					m--;
					continue;
				}
				if(xxl)//大两号
				{
					cout<<"XXL"<<endl;
					xxl--;
					continue;
				}
				if(s)//小两号
				{
					cout<<"S"<<endl;
					s--;
					continue;
				}
			}
		}
		if(a=="XL")//其它都一个道理~~~
		{
			if(xl)
			{
				cout<<"XL"<<endl;
				xl--;
			}
			else
			{
				if(xxl)
				{
					cout<<"XXL"<<endl;
					xxl--;
					continue;
				}
				if(l)
				{
					cout<<"L"<<endl;
					l--;
					continue;
				}
				if(m)
				{
					cout<<"M"<<endl;
					m--;
					continue;
				}
				if(s)
				{
					cout<<"S"<<endl;
					s--;
					continue;
				}
			}
		}
		if(a=="XXL")
		{
			if(xxl)
			{
				cout<<"XXL"<<endl;
				xxl--;
			}
			else
			{
				if(xl)
				{
					cout<<"XL"<<endl;
					xl--;
					continue;
				}
				if(l)
				{
					cout<<"L"<<endl;
					l--;
					continue;
				}
				if(m)
				{
					cout<<"M"<<endl;
					m--;
					continue;
				}
				if(s)
				{
					cout<<"S"<<endl;
					s--;
					continue;
				}
			}
		}
	} 
	return 0;//拜拜~
}
```

走过路过，点个赞呀(〃'▽'〃)

---

## 作者：yzyjh (赞：1)

看到前几位大佬都用了一堆if，其实用一个map就可以解决。

### 思路
**用map对应每个型号的衣服编号**

上代码：

```cpp
#include<bits/stdc++.h>//万能头文件
#define ll long long
#define dl double
using namespace std;
int a[17];
int main()
{
    cin >> a[5] >> a[6] >> a[7] >> a[8] >> a[9];//读入
 
    map<string, int> mp;
    map<int, string> rp;//马上就要noip了，祝大家rp++
    mp["S"] = 5, rp[5] = "S";//衣服和编号对应
    mp["M"] = 6, rp[6] = "M";//同上
    mp["L"] = 7, rp[7] = "L";//同上
    mp["XL"] = 8, rp[8] = "XL";//同上
    mp["XXL"] = 9, rp[9] = "XXL";//同上
    int k;//一共k个人
    cin >> k;//读入
    for(int i = 0; i < k; i++){
        string s;
        cin >> s;
 			//不管这个位置有没有衣服，直接循环判断
        for(int j = 0; j < 5; j++){
            if(a[mp[s] + j] > 0){//如果比他型号大的有衣服
                cout << rp[mp[s] + j] << endl;//没有合身的当然是大一点的好，有输出都一样，所以应该把大的放前面
                a[mp[s] + j]--;//用完一件衣服就要减去掉
                break;//这个人有了衣服就跳出循环
            }
            else if(a[mp[s] - j] > 0){/如果比他型号小的有衣服
                cout << rp[mp[s] - j] << endl;//如果比大号的先出现，就输出这一件
                a[mp[s] - j]--;//用完一件衣服就要减去掉
                break;//同上
            }
        }
    }
    return 0;//完结散花
}
```


---

## 作者：林家三少 (赞：1)

一个$\color{red}\text{ 纯模拟 }$的$\color{orange}\text{ 普及- }$的题

我们只需要一大堆$if$来判断，怎么判断呢？大概如下：

- 如果正好有一件尺码相同的，就直接拿那件，

- 没有的话就先向上找一个尺码，然后再向下找，

- 以此类推$...$

比如说有个人要拿$L$码的，我们找的顺序是$L,XL,M,XXL,S$

然后我们记得要用$else$ 或 $continue$，因为我们是直接判断剩余数量的，如果不用不免会有输出多个尺码的情况

所以就有了这个很短($chang$)的代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
int s,m,l,xl,xxl;
string a;
int n;
int main(){
	cin>>s>>m>>l>>xl>>xxl;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		if(a=="S"){
			if(s>0){
				s--;
				cout<<"S\n";
			}
			else{
				if(m>0){
					m--;
					cout<<"M\n";
				}
				else{
					if(l>0){
						l--;
						cout<<"L\n";
					}
					else{
						if(xl>0){
							xl--;
							cout<<"XL\n";
						}
						else{
							if(xxl>0){
								xxl--;
								cout<<"XXL\n";
							}
						}
					}
				}
			}
		}
		if(a=="M"){
			if(m>0){
				m--;
				cout<<"M\n";
			}
			else{
				if(l>0){
					l--;
					cout<<"L\n";
				}
				else{
					if(s>0){
						s--;
						cout<<"S\n";
					}
					else{
						if(xl>0){
							xl--;
							cout<<"XL\n";
						}
						else{
							if(xxl>0){
								xxl--;
								cout<<"XXL\n";
							}
						}
					}
				}
			}
		}
		if(a=="L"){
			if(l>0){
				l--;
				cout<<"L\n";
			}
			else{
				if(xl>0){
					xl--;
					cout<<"XL\n";
				}
				else{
					if(m>0){
						m--;
						cout<<"M\n";
					}
					else{
						if(xxl>0){
							xxl--;
							cout<<"XXL\n";
						}
						else{
							if(s>0){
								s--;
								cout<<"S\n";
							}
						}
					}
				}
			}
		}
		if(a=="XL"){
			if(xl>0){
				xl--;
				cout<<"XL\n";
			}
			else{
				if(xxl>0){
					xxl--;
					cout<<"XXL\n";
				}
				else{
					if(l>0){
						l--;
						cout<<"L\n";
					}
					else{
						if(m>0){
							m--;
							cout<<"M\n";
						}
						else{
							if(s>0){
								s--;
								cout<<"S\n";
							}
						}
					}
				}
			}
		}
		if(a=="XXL"){
			if(xxl>0){
				xxl--;
				cout<<"XXL\n";
			}
			else{
				if(xl>0){
					xl--;
					cout<<"XL\n";
				}
				else{
					if(l>0){
						l--;
						cout<<"L\n";
					}
					else{
						if(m>0){
							m--;
							cout<<"M\n";
						}
						else{
							if(s>0){
								s--;
								cout<<"S\n";
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
```


---

## 作者：锦瑟，华年 (赞：1)

恩下面同学的代码太长了，我发一篇短的。

这题没什么难度，我建议把$S,M,L,XL,XXL$ ,分别转化成 $1,2,3,4,5$，然后再模拟，对于选衣服的那段代码，我们可以先设一个 $j$ , 从0开始从小到大遍历，选的衣服的编号就是原来的编号再加上 $j$ ，至于判断什么的，我就无需再讲了吧？（看不懂代码也有注释）

好了，上代码：

	#include<stdio.h>
	using namespace std;
	char s[10];
	int a[10];
	int main(){
		int n,i,j;
		scanf("%d%d%d%d%d%d",&a[1],&a[2],&a[3],&a[4],&a[5],&n);//读入，a[1]~a[5]分别表示S,M,L,XL,XXL的件数
		for(i=1;i<=n;i++){
			scanf("%s",s);//读入
			int k;
			if(s[0]=='S')k=1;//转化，S,M,L,XL,XXL ,分别转化成1,2,3,4,5
			if(s[0]=='M')k=2;
			if(s[0]=='L')k=3;
			if(s[0]=='X'&&s[1]=='L')k=4;
			if(s[0]=='X'&&s[1]=='X'&&s[2]=='L')k=5;
			for(j=0;k+j<=5||k-j>0;j++){//选择衣服
				if(a[k+j]){//先选大的
					a[k+j]--;
					if(k+j==1)printf("S\n");//按照编号输出
					if(k+j==2)printf("M\n");
					if(k+j==3)printf("L\n");
					if(k+j==4)printf("XL\n");
					if(k+j==5)printf("XXL\n");
					break;//一定要加，否则可能会输出两个尺码
				}
				if(a[k-j]){//再选小的
					a[k-j]--;
					if(k-j==1)printf("S\n");
					if(k-j==2)printf("M\n");
					if(k-j==3)printf("L\n");
					if(k-j==4)printf("XL\n");
					if(k-j==5)printf("XXL\n");
					break;
				}
			}
		}
		return 0;
	}
    
好了，byebye~~~.

---

## 作者：Eason_AC (赞：0)

## Content
有一家服装店，有 $\texttt{S}$ 码的衣服 $n_S$ 件、$\texttt{M}$ 码的衣服 $n_M$ 件，$\texttt{L}$ 码的衣服 $n_L$ 件，$\texttt{XL}$ 码的衣服 $n_{XL}$ 件，$\texttt{XXL}$ 码的衣服 $n_{XXL}$ 件。

有 $k$ 个人依次进来买衣服，每个人都有自己期望的尺码。如果服装店里面刚好有这个尺码的衣服，TA 就会拿上这件衣服离开，否则 TA 会选择尽可能接近自己的期望尺码的衣服（如果在这样的情况下有多种选择，则选择尺码较大的）。求这 $k$ 个人最后各拿了什么尺码的衣服。

**数据范围：$1\leqslant n_S,n_M,n_L,n_{XL},n_{XXL}\leqslant 1000,1\leqslant k\leqslant n_S+n_M+n_L+n_{XL}+n_{XXL}\leqslant 1000$。**
## Solution
这题目模拟就好，就是代码稍微长了一些。

我们先看是否有每个人的期望尺码的衣服，如果有那就直接选择，否则分别向大尺码和小尺码依次遍历，大尺码先遍历到就选择大尺码，小尺码先遍历到就选择小尺码。因为数据的特殊性，无需判断是否有足够的衣服。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

int sze[7], k;
string str;
const string ans[6] = {"", "S", "M", "L", "XL", "XXL"};

int main() {
	for(int i = 1; i <= 5; ++i)	scanf("%d", &sze[i]);
	scanf("%d", &k);
	while(k--) {
		cin >> str;
		if(str == "S") {
			if(sze[1]) {puts("S"); sze[1]--;}
			else {
				int cur = 1;
				while(1) {
					cur = min(5, cur + 1);
					if(sze[cur]) {
						cout << ans[cur] << endl;
						sze[cur]--;
						break;
					}
				}
			}
		} else if(str == "M") {
			if(sze[2]) {puts("M"); sze[2]--;}
			else {
				int curl = 2, curr = 2;
				while(1) {
					curl = max(1, curl - 1), curr = min(5, curr + 1);
					if(sze[curr]) {
						cout << ans[curr] << endl;
						sze[curr]--;
						break;
					} else if(sze[curl]) {
						cout << ans[curl] << endl;
						sze[curl]--;
						break;
					}
				}
			}
		} else if(str == "L") {
			if(sze[3]) {puts("L"); sze[3]--;}
			else {
				int curl = 3, curr = 3;
				while(1) {
					curl = max(1, curl - 1), curr = min(5, curr + 1);
					if(sze[curr]) {
						cout << ans[curr] << endl;
						sze[curr]--;
						break;
					} else if(sze[curl]){
						cout << ans[curl] << endl;
						sze[curl]--;
						break;
					}
				}
			}
		} else if(str == "XL") {
			if(sze[4]) {puts("XL"); sze[4]--;}
			else {
				int curl = 4, curr = 4;
				while(1) {
					curl = max(1, curl - 1), curr = min(5, curr + 1);
					if(sze[curr]) {
						cout << ans[curr] << endl;
						sze[curr]--;
						break;
					} else if(sze[curl]) {
						cout << ans[curl] << endl;
						sze[curl]--;
						break;
					}
				}
			}
		} else if(str == "XXL") {
			if(sze[5]) {puts("XXL"); sze[5]--;}
			else {
				int cur = 5;
				while(1) {
					cur = max(1, cur - 1);
					if(sze[cur]) {
						cout << ans[cur] << endl;
						sze[cur]--;
						break;
					}
				}
			}
		}
	}
}
```

---

## 作者：soho_andy (赞：0)

我想着把码数转换成数字1到5，然后按照题目要求模拟每一个队员的选择（原选择>大码>小码，并且大小码与原选择尽量接近）最后将数字转换回码数即可。

```c
#include <iostream>
#include <cstdio>
using namespace std;
int k,x,a[10],ans[1005];
string s;

int ck(string s){//判断每个人最后选哪件衣服
	把码数转换成数字
	if(s=="S") x=1;
	else if(s=="M") x=2;
	else if(s=="L") x=3;
	else if(s=="XL") x=4;
	else x=5;
   
	if(a[x])   { a[x]--;return x; }
	if(a[x+1]) { a[x+1]--;return x+1; }//优先选大码
	if(a[x-1]) { a[x+1]--;return x-1; }//要求与原选择尽量接近，所以下一个看小码
	if(a[x+2]) { a[x+1]--;return x+2; }
	if(a[x-2]) { a[x+1]--;return x-2; }
	if(a[x+3]) { a[x+1]--;return x+3; }
	if(a[x-3]) { a[x+1]--;return x-3; }
	if(a[x+4]) { a[x+1]--;return x+4; }
	if(a[x-4]) { a[x+1]--;return x-4; }
}

int main(){
	//输入
	for(int i=1;i<=5;i++) scanf("%d",&a[i]);//每个码数的衣服有几份
	scanf("%d",&k);//队员数
	for(int i=1;i<=k;i++){
		cin>>s;
		ans[i]=ck(s);//ans：每个人最后的选择
	}
    
	for(int i=1;i<=k;i++){
		if(ans[i]==1) printf("S\n");//再把数字转换回码数
		if(ans[i]==2) printf("M\n");
		if(ans[i]==3) printf("L\n");
		if(ans[i]==4) printf("XL\n");
		if(ans[i]==5) printf("XXL\n");
	}
    
	return 0;
}
```


---

## 作者：cherubim (赞：0)

~~我可不会告诉你因为蒟蒻太菜调了半天~~

题意是：有 $ s $ , $ m $ , $ l $ , $ xl $ , $ xxl $ ,这么大的衣服，现在各有 $ a $ , $ b $ , $ c $ , $ d $ , $ e $ 件。现在给你任意一个尺码，如果这个尺码的衣服还有，就拿走它 （数量减少一）。如果没有，就按照“先大后小”的原则，寻找和他大小接近的衣服。

算法肯定是枚举。不过如果纯模拟，用一堆 if 来判断选哪个衣服的话，代码太过冗长。所以我考虑到用一个二维数组来模拟衣服大小的优先级关系（将题目中给的尺码转化为数字操作）。在读入后就用函数将衣服型号转化为数字，按照二维数组中的优先级枚举，如果有，就选最近的（因为是按优先级排序所以枚举的顺序是最优答案），如果没有，就按照优先级顺序依次枚举下一个。因为题目保证肯定有答案，所以肯定能在优先级中枚举到。

感觉讲起来很复杂，但是代码很简单。其余的注释都在代码里了。

PS.初始化二维数组的时候记得注意下标。

## CODE

```cpp
#include <bits/stdc++.h>

using namespace std ; 

int num[5] ; 
int n ; 
string qus ; 
bool flag = false ; 
//下面的数组定义优先级对应关系：
//s -> 1 | m -> 2 | l -> 3 | xl -> 4 | xxl -> 5
int vis[5][5] = { { 0 , 1 , 2 , 3 , 4 } ,
				{ 1 , 2 , 0 , 3 , 4 } ,
				{ 2 , 3 , 1 , 4 , 0 } ,
				{ 3 , 4 , 2 , 1 , 0 } ,
				{ 4 , 3 , 2 , 1 , 0 } } ;  

inline int read ( string s ){ // 询问转化 
	if ( s == "S" ) return 0 ; 
	if ( s == "M" ) return 1 ; 
	if ( s == "L" ) return 2 ; 
	if ( s == "XL" ) return 3 ; 
	if ( s == "XXL" ) return 4 ; 
}
inline string print ( int n ) { // 输出转化 
	if ( n == 0 ) return "S" ; 
	if ( n == 1 ) return "M" ; 
	if ( n == 2 ) return "L" ; 
	if ( n == 3 ) return "XL" ; 
	if ( n == 4 ) return "XXL" ; 
}

int main ( ) 
{
	for ( int i = 0 ; i < 5 ; ++ i ) cin >> num[i] ;  
	cin >> n ; 
	while ( n -- )
	{
		cin >> qus ; 
		int s = read ( qus ) ;
		for ( int j = 0 ; j < 5 ; ++ j ){
			if ( num[ vis[s][j] ] > 0 ) { //按照优先级枚举，如果还有的话 
				num[ vis[s][j] ] -- ;
				cout << print ( vis[s][j] ) << endl ;
				break ; //找到后就退出循环 
			}
		}
	}
	return 0 ; //撒花 ~ 
}

```


---

