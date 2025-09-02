# One Bomb

## 题目描述

你接到了一个拆除工作：

有一个 $n*m$ 个单元格的仓库，其中每个格子只可能是"."或"*"。

"."表示该格子为空，"*"表示这里有一面墙。

现在你有一枚炸弹，可以爆破所有同行或同列的墙(它既可以放在墙内，也可以放在空单元格)

请你找出一种放置炸弹的方式，使得所有的墙都能被清除。

## 样例 #1

### 输入

```
3 4
.*..
....
.*..
```

### 输出

```
YES
1 2
```

## 样例 #2

### 输入

```
3 3
..*
.*.
*..
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
6 5
..*..
..*..
*****
..*..
..*..
..*..
```

### 输出

```
YES
3 3
```

# 题解

## 作者：happybob (赞：4)

我这不知道什么时候做的了……思路和大家应该是一样的了，不说多的了，就贴个代码吧：

```cpp
#include <cstdio>
#include <iostream>
using namespace std;

char a[1005][1005];
int cn[1005], cm[1005];

int main()
{
    int n, m, cnt = 0, cnt2 = 0;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            cin >> a[i][j];
            if(a[i][j] == '*')
            {
                cnt++;
    			cn[i]++;
    			cm[j]++;
            }
        }
    }
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            cnt2 = cn[i] + cm[j];
            if(a[i][j] == '*')
            {
                cnt2--;
            }
            if(cnt2 == cnt)
            {
                printf("YES\n%d %d\n", i, j);
                return 0;
            }
        }
    }
    printf("NO\n");
    return 0;
}
```

速度有点慢

---

## 作者：fls233666 (赞：2)

看到这题只有一个炸弹要放置时，我马上去看了$n$和$m$的范围：

$1<=n,m<=1000$

**也就是说，即使把整个矩阵遍历一遍，最坏的情况是尝试放置$10^{6}$次！**

看来可以**枚举**矩阵的每个位置放置炸弹的结果，不会超时。


## 代码实现过程


首先肯定要一个char数组来存储整个矩阵，同时用一个变量来统计矩阵中有多少个'*'（即统计总共有多少面墙）

```cpp
//读入n和m的数值
int z=0;
char mp[n+1][m+1];
for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
		cin>>mp[i][j];
		if(mp[i][j]=='*')
			z++;
	}                      
}
```

然后是遍历整个矩阵，统计如果把地雷放在$(i,j)$能炸掉的墙的总数$s$，然后比较$s$与$z$是否相等，如果是直接输出答案**并结束程序**。如果遍历完成后，没有找到答案，输出NO.

```cpp
for(int i=1;i<=n;i++){
	for(int s,j=1;j<=m;j++){
		//统计能炸掉的墙的总数，并存到变量s中
		if(s==z){
			cout<<"YES"<<endl<<i<<" "<<j;
			return 0;
		}
	}                      
}
cout<<"NO";
return 0;
```

接下来我们想，因为枚举的复杂度已经略高了，**如果我们再搞一重循环进行统计，超时的概率很大**。所以如何进行快速的统计呢？

我们可以开两个int数组$zn$和$zm$。$zn[i]$表示第$i$行的墙的总数，$zm[i]$表示第$i$列的墙的总数。而且这两个数组的统计都可以在读入矩阵时完成。

```cpp
//读入n和m的数值
int z=0,zn[n+1],zm[m+1];
char mp[n+1][m+1];
memset(zn,0,sizeof(zn));
memset(zm,0,sizeof(zm));
//不能忘记初始化
for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
		cin>>mp[i][j];
		if(mp[i][j]=='*'){
			z++;
			zn[i]++;
			zm[j]++;
		}
	}                      
}
```

**统计$(i,j)$的墙的总数只要计算$zn[i]+zm[j]$即可！**

要注意的是，**如果$(i,j)$的位置上是一面墙，那么这面墙会被重复计算一次**。这时$s$要**减一**。

完整代码如下：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main(){
    int n,m,z=0;
    cin>>n>>m;
    char mp[n+1][m+1];
    int zn[n+1],zm[m+1];
    memset(zn,0,sizeof(zn));
    memset(zm,0,sizeof(zm));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>mp[i][j];
            if(mp[i][j]=='*'){
                zn[i]++;
                zm[j]++;
                z++;
            }
        }
    }
  //数据初始化操作
  
    for(int i=1;i<=n;i++){
        for(int s,j=1;j<=m;j++){
            s=zn[i]+zm[j];
            if(mp[i][j]=='*')
                s--;
            if(z==s){
  				//找到答案，输出并结束程序
                cout<<"YES"<<endl<<i<<" "<<j;
                return 0;
            }
        }
    }
  //枚举寻找答案
  
    cout<<"NO";  //无解
    return 0;
}
```


---

## 作者：ADivT (赞：2)

## 本人太菜了

一看题，发现$ n,m<=1000$ 自然想到$O(n^2)$的做法,统计每一行列地雷的个数,直接输出即可,需要注意如该点为雷,需减去重复计数的1,~~高清无码~~代码如下(三目运算符的优先级卡了我半小时)。
```cpp
#include<bits/stdc++.h>

#define rep(i,o,p) for(register int i=o;i<=p;++i)

using namespace std; 

int n,m,is_p=0,tot=0;
char str[1010][1010];
int l[1010]={},r[1010]={};

int  main(){
	scanf("%d %d\n",&n,&m);
	rep(i,1,n){
		rep(j,1,m){
			str[i][j]=getchar();
			if(str[i][j]=='*'){
				++l[i],++r[j],++tot; 
			}
		}
		getchar();
	}
	rep(i,1,n){
		rep(j,1,m){
			int s=l[i]+r[j]+((str[i][j]=='*')?-1:0);
			if(!(tot-s)&&(!is_p))is_p=printf("YES\n%d %d\n",i,j);
		}
	}
	if(!is_p)printf("NO\n");
	return 0;
}
```
以上，就是本题的題解，看在我写了半小时的份上，留个赞再走呗


---

## 作者：thomas_zjl (赞：1)

这是一道模拟题。

## 题目大意.

输入一个带有 $*$ 或 $\ .\ $ 的矩阵，来求是否有一个位置的同行同列中有所有的 $*$ 。

## 做题思路。

先特判，我特判了 4 种情况。

- 当 n 为 1 或 m 为 1 ， 直接输出 YES , 位置为 $（1,1)$。

- 当 $*$ 数为 0 时， 代表没有一个点 ， 输出 YES ,位置为 $(1,1)$。

- 当 $*$ 数为 1 时， 代表只有 1 个点，输出 YES ,位置就在那个点。

- 当 $*$ 数为 2 是， 代表有 2 个点， 输出 YES ,位置在 第一个点的 x 轴和第二个点的 y 轴 或 第二个点的 x 轴和第一个点的 y 轴。

接下来就是一个枚举了，因为我们可以用二个桶在保存每个 x 轴 和 y 轴上有的点数。

每个点的每行每列的点数为这二个桶之和。

如果这个点也是个 $*$ , 要减一。

如果最后的值相加为 $*$ 数，输出 YES，位置为那个点，结束程序。

如果没有这个点，输出 NO 。

接下来就是代码了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int x[1001];//记录每行有多少 “*”。
int y[1001];//记录每列有多少 “*”。
struct point{
	int x,y;
}a[1000007];//每一个点的位置。
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;
	char c[1001][1001];
	int p=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>c[i][j];
			if(c[i][j]=='*'){
				x[i]++;
				y[j]++;
  				//改变这二个桶。
				p++;//“*”的数量增加。
				a[p].x=i;
				a[p].y=j;
  				//储存每个“*”的位置。
			}
		} 
	}
	if(n==1||m==1){
		cout<<"YES"<<endl<<1<<' '<<1;
		return 0;
	}
	if(p==0){
		cout<<"YES"<<endl<<1<<' '<<1;
		return 0;
	}
	if(p==1){
		cout<<"YES"<<endl<<a[1].x<<' '<<a[1].y;
		return 0;
	} 
	if(p==2){
		cout<<"YES"<<endl<<a[1].x<<' '<<a[2].y;
		return 0;
	}
  	//以上为特判。
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int xxx=x[i]+y[j];//来记录每行与每列的和。
			if(c[i][j]=='*') --xxx;
 			//当这个点为“*”时要减一。
			if(xxx==p){//如果为点数,输出 YES , 答案为 i , j。
				cout<<"YES"<<endl<<i<<' '<<j;
				return 0;//结束程序。
			}
		}
	} 
	cout<<"NO";//如果在上面的循环没有结束，代表无解，输出 NO。
}

```


---

## 作者：alex_liu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF699B)

# 思路：
大模拟，枚举每一个格子是否可以炸掉所有墙面就好了。

$n$ 和 $m$ 范围非常小，所以暴力完全可以过。

$$(1 \le n , m \le 1000)$$

# AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){//快读优化。
  	int x=0,f=1;
  	char c=getchar();
  	for(;c<'0'||c>'9';c=getchar())
    	if(c=='-')f=-1;
  	for(;c<='9'&&c>='0';c=getchar())
    	x=(x<<3)+(x<<1)+c-'0';
  	return x*f;
}
int n,m,ans=0;//ans存储地图中的墙面数。
char c[1005][1005];//地图。 
int h[1005]={0},l[1005]={0};//h[i]代表第i行有多少个墙，l[j]代表第j行有多少个墙。
signed main(){
	n=read(),m=read();//输入。
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			c[i][j]=getchar();//输入。 
			if(c[i][j]=='*')h[i]++,l[j]++,ans++;//当前位置为墙面时，则行、列、总数组的值均加一。
		}
		getchar();//注意换行符。
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int sum=h[i]+l[j];//定义sum为当前位置可以炸到的所有墙面。
			if(c[i][j]=='*')sum--;//可以想想为什么要特判（思考题）
			if(sum==ans){//如果当前可以炸掉的墙面与地图中的墙面数相同。 
				cout<<"YES"<<endl<<i<<" "<<j<<endl;//输出炸弹坐标。
				return 0;//结束程序。 
			}
		}
	}
	cout<<"NO"<<endl;//炸不完 。
	return 0;//结束程序。 
}
```
## 思考题答案：

因为当前为如果是墙面的话，当前行和列都有将这个墙面算进去，所以要去重（总量 $-1$ ）。



---

## 作者：瀛洲仙子 (赞：0)

### 样例分析
我们把可以炸到的墙表示为 `&`，反之为 `*`    
#### 样例 1 ：    
可以炸到如下位置。
```
&&&&
*&**
*&**
```
### 思路分析   

这是一道模拟题，通过循环遍历，求出炸弹应该摆放的位置。

首先输入 $n$，$m$，不用解释。
```python
n,m=input().split(' ')
n,m=int(n),int(m)
```
接下来声明二维列表存储墙壁信息，并输入列表，采用
`for` 循环。
```python
wl=[]
for i in range(n):
		wl.append(input('').split(''))
```
然后需要定义一个方法，表示选择位置。
* 首先遍历选择每一个位置，并判断是否是合适的元素。
* 如果是合适的元素，返回这个元素，否则在最后返回 $(2147483647,2147483647)$，表示不行。

```python
def choosepos(r):#r 表示墙壁信息，返回值为一个元组
		for i in range(len(r)):
        	for j in range(len(i)):
        		nw=bombared(r,i,j)
                	if alldest(nw):
                			return (i,j)
      	return (2147483647,2147483647)
```
大家可以看到，我们还需要两个方法，就是
`bombared(r,i,j)` 和 `alldest(nw)`，分别表示炸弹爆发以后的状态，和是否所有的墙壁都被炸毁，先者返回一个二维数组，后者返回一个
`boolean`。    

首先研究
`bombared(e,i,j)`，接收的三个参数，分别为一个列表，两个整数，表示地图和炸弹所在的点。   
该函数的作用就是将所有能红炸到的点进行标记，并返回标记完了的地图。

```python
def bombared(r,i,j):
	for ie in range(len(r)):
    	r[ie][j]='.'
   for je in range(len(r[i])):
   		r[i][je]='.'
   return r
```

第二个函数，判断墙是否全部被轰炸，需要一个二维列表，返回一个
`boolean`，表示是否全部被轰炸。
* 遍历全部元素：
	* 如果还有元素为 `*`，那么直接返回 `False`。
    * 如果全部元素都为 `.`，返回 `True`。    

具体代码如下。
```python
def alldest(r):
		for i in r:
        	for j in i:
        			if j=='*':
                		return False
        return True
```
最后在全局调用 `choosepos`函数，并且返回结果。
```python
if choosepos(wl)==(2147483647,2147483647):
		print("NO")
else:
		print("YES\n{} {}".format(choosepos(wl)[0],choosepos(wl)[1]))
```
### 代码分享
这道题代码长了一点，但是不算难以理解，无注释代码如下。
```python
n,m=input().split(' ')
n,m=int(n),int(m)
wl=[]
for i in range(n):
		wl.append(input('').split(''))
def bombared(r,i,j):
	for ie in range(len(r)):
    	r[ie][j]='.'
   for je in range(len(r[i])):
   		r[i][je]='.'
   return r
def alldest(r):
		for i in r:
        	for j in i:
        			if j=='*':
                		return False
        return True
def choosepos(r):#r 表示墙壁信息，返回值为一个元组
		for i in range(len(r)):
        	for j in range(len(i)):
        		nw=bombared(r,i,j)
                	if alldest(nw):
                			return (i,j)
      	return (2147483647,2147483647)
if choosepos(wl)==(2147483647,2147483647):
		print("NO")
else:
		print("YES\n{} {}".format(choosepos(wl)[0],choosepos(wl)[1]))
```
**珍爱生命，远离抄袭！**    
### 更新记录
* datetime.date(2022,2,18) 精简题解，删除废话，麻烦管理再次审核！谢谢！

---

## 作者：Snow_Dreams (赞：0)


这道题可以用一个数学方法

我们先判断是否可以被清除：

在读入的过程中用两个vis数组记录每个出现 * 的坐标
接着，我们发现，当且仅当有三面墙有不同的行，列
比如说样例2，发现三个 * 处在不同行与列的地方，
所以直接输出NO，并结束程序

接着我们就先输出Yes

随后我们需要判断这枚炸弹的地方，这个十分简单

我们就将vis为真的地方依次试一遍就可以了

这个算法时间复杂度仅为输入时的 O(n^2)（O(n * m)）

题目中说n，m均小于等于1000，所以时间复杂度为1e6

试完以后就将用变量记录的x，y输出即可



---

