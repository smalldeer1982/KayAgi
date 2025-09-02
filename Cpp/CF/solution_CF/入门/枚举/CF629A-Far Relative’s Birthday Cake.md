# Far Relative’s Birthday Cake

## 题目描述

多尔的家人正在庆祝多尔的生日派对。他们爱多尔，所以他们计划让他的生日蛋糕变得不可思议的！

蛋糕是一个由n×n的等边正方形组成的形状，长度为1。每个方块要么是空的，要么是由一个巧克力组成的。他们买了蛋糕，便开始把巧克力放在蛋糕上。“家庭之门”的幸福值等于蛋糕中同一行或同一列中装有巧克力的一对细胞的数量。多尔的家人想知道他们的幸福程度是多少？

## 样例 #1

### 输入

```
3
.CC
C..
C.C
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4
CC..
C..C
.CC.
.CC.
```

### 输出

```
9
```

# 题解

## 作者：YuanZhizheng (赞：20)

看题解里面都没有**DFS**，那我就来一发**DFS**吧！
先说要点吧！
# 要点
这题找的是一对巧克力，只用顺着一个一行和一列中的一个方向去找就可以了。

**例如**- 第一行第一列有一个巧克力，第一行第二列也有一个巧克力，当第
一行第一列

的巧克力找到了第一行第二列的巧克力后，第一行第二列的巧克力无需回去找第一行

第一列的巧克力。同列也是这个道理

下面上AC代码

```
#include<bits/stdc++.h>//万能头文件
using namespace std;//C++必备
char s[105][105];//用于接收输入的字符串
bool vis[105][105];//标记数组，作用之后会说
ll num=0;//用来记录幸福指数
int n;//接收题目行列数n
int i,j;//用于循环的变量，作为全局变量还有一些作用会在接下来提到
bool check(int x,int y)
{
    if(x==i&&y<n)//检测是否在同一行，是的话继续搜索对应①1
        return 1;
    else if(x<n&&y==j)//用于检查是否在同一列，是的话继续搜索对应②2
        return 1;
    return 0;
}
void dfs(int x,int y)//DFS，本程序主干
{
    if(check(x,y))
    {
        if(s[x][y]=='C'&&vis[x][y]==0)//标记数组为0才记录，不然会出现自己与自己成一对的情况
        {
            num++;
        }
        dfs(x,y+1);//①1
        dfs(x+1,y);//②2
    }
}
int main()
{
    cin>>n;//接收行列数n
    for(i=0; i<n; i++)
    {
        scanf("%s",s[i]);//接收“生日蛋糕”的字符串
    }
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(s[i][j]=='C')
            {
                vis[i][j]=1;//将自身标记为1，防止自己和自己配对
                dfs(i,j);//搜到之后，以当前i，j作为起点，进行搜索
                vis[i][j]=0;//清除标记
            }
        }
    }
    printf("%lld",num);
    return 0;
}
```
如果还有哪里不清楚可以在评论提问，会及时回答


---

## 作者：test_check (赞：10)

一道简单的问题，我们一步一步来解决。

------------
$$First:\text{输入}$$
输入十分简单，首先，$cin>>n$，输入$n$之后，两重$for$循环，将题目所要输入的矩阵输进去，像这样$↓↓↓$
```cpp
    for(int i=1;i<=n;i++)
     for(int j=1;j<=n;j++)
      cin>>ch[i][j];  
``` 
注意了，$ch[][]$应该是一个字符类型$(char)$的数组

------------
$$Second:\text{解决问题}$$
根据题意，$C$就是含有巧克力的细胞,我们可以用两个双重$for$循环，一遍遍历每一个竖列，一遍遍历每一个横列。，用$c$来表示一共有几对巧克力的细胞，$t$来表示“家庭之门”幸福感的价值，根据
$$\text{当}c=1\text{时}\ ,t=0$$
$$\text{当}c=2\text{时}\ ,t=1$$
$$\text{当}c=3\text{时}\ ,t=3$$
$$\text{当}c=4\text{时}\ ,t=6$$
$$\text{当}c=5\text{时}\ ,t=10$$
根据数学方法，可得$\huge t=\frac{c\times(c-1)}{2}$应为要统计每一行/列$t$的个数，所以，可用以下方法遍历矩阵$↓↓↓$
```cpp
    for(int i=1;i<=n;i++)
	{
		c=0;   //初始化
		for(int j=1;j<=n;j++)
		{
			if(ch[i][j]=='C')
			c++;
		}
		t+=(c*(c-1))/2;  //更新t的值
	}
	for(int j=1;j<=n;j++)
	{
		c=0;   //初始化
		for(int i=1;i<=n;i++)
		{
			if(ch[i][j]=='C')
			c++;
		}
		t+=(c*(c-1))/2;  //更新t的值
	}
```
最后$cout<<t$即可。

------------

$My \ complete \ code:$
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n,t=0,c=0; //初始化
	char ch[105][105];
	cin>>n;
	for(int i=1;i<=n;i++)
	 for(int j=1;j<=n;j++)
	  cin>>ch[i][j];   //输入
	for(int i=1;i<=n;i++)
	{
		c=0;
		for(int j=1;j<=n;j++)
		{
			if(ch[i][j]=='C')
			c++;
		}
		t+=(c*(c-1))/2;
	}            //横向遍历
	for(int j=1;j<=n;j++)
	{
		c=0;
		for(int i=1;i<=n;i++)
		{
			if(ch[i][j]=='C')
			c++;
		}
		t+=(c*(c-1))/2;
	}          //竖向遍历
	cout<<t;
}
```

---

## 作者：judgejudge (赞：6)

# 高斯求和公式！！！
这道题重在理解，怎样才能计算同一行或同一列的细胞呢？？？

我们举个例子：
|  1|2  | 3 |
| -----------: | -----------: | -----------: |
| C |C  | C |

这里面有几个细胞呢？？

我们可以让**1，2；1，3；2，3**分别搭配，算出来就有**3**组细胞。

同样的道理，4个C有6组，5个C有10组......

我们研究一下组数：1，3，6，10**这不就是高斯求和公式吗？？？**

所以我们可以先查找这一行或这一列有几个C，然后把高斯求和公式往里一带（注意：此处的公式是**n*(n-1)/2**）

所以就有了代码：
```cpp
#include <iostream>
using namespace std;
char c[10001][10001];
long long sum=0;
int main(){
	int i,j,k,n,l;
	cin>>n;
	for(i=1;i<=n;i++)
	for(j=1;j<=n;j++)cin>>c[i][j];//输入这个字符数组
	for(i=1;i<=n;i++){
		k=0;
		l=0;
	    for(j=1;j<=n;j++){//此处我们行和列同时判断，减小时间复杂度
	    	if(c[i][j]=='C')k++;//此处用k和l分别区分行和列
	    	if(c[j][i]=='C')l++;
		}
		sum+=(k*(k-1))/2+(l*(l-1))/2;//代入n*(n-1)/2
	}
	cout<<sum<<endl;//输出
	return 0;
}
```
[我的测评记录](https://www.luogu.org/recordnew/show/17309428)


---

## 作者：Viston (赞：5)

This Explanation is written by viston. (If you do many red subjects ,you'll sometimes see me).

好的让我们开始讲中文！   
实际上我觉得这题很适合用~~DFS~~,但蒟蒻不想写于是就用了一个枚举23333   
但这题数据这么小，还是可以的额   
记住不要从头枚举，会X2的。  

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long ans=0;
    int a,b,i;
    char c[102][102];
    cin>>a;
    for(i=1;i<=a;i++)
        for(int j=1;j<=a;j++)
            cin>>c[i][j];
    for(i=1;i<=a;i++)
        for(int j=1;j<=a;j++)
            if(c[i][j]=='C')//如果为C
            {
                for(int k=i+1;k<=a;k++)//从下一位开始枚举
                    if(c[k][j]=='C')//纵行
                        ans++;
                for(int k=j+1;k<=a;k++)//横行
                    if(c[i][k]=='C')
                        ans++;
            }
    cout<<ans;
    return 0;
}
```
See you Next red subject!

---

## 作者：Porsche (赞：2)

今天晚上的第二道题解,我的网不快，但是事实证明我的是最优解，啦啦啦~

思路非常简单，首先要把所有的“C”标记为1，所有的“.”标记为0，然后找出每行每列1的个数，找规律发现此行此列有n个1则会有（1+2+……+n-1）对巧克力，为方便提前打表降低时间复杂度，然后输出加和即可。

话不多说，贴代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int Map[101][101]; 
int flag[101]={0,1,3,6,10,15,21,28,36,45,55,66,78,91,105,120,136,153,171,190,210,231,253,276,300,325,351,378,406,435,465,496,528,561,595,630,666,703,741,780,820,861,903,946,990,1035,1081,1128,1176,1225,1275,1326,1378,1431,1485,1540,1596,1653,1711,1770,1830,1891,1953,2016,2080,2145,2211,2278,2346,2415,2485,2556,2628,2701,2775,2850,2926,3003,3081,3160,3240,3321,3403,3486,3570,3655,3741,3828,3916,4005,4095,4186,4278,4371,4465,4560,4656,4753,4851,4950,5050};//打表出奇迹
int main()
{
	int n;
	scanf("%d",&n);
	char ch[101];
	int ans=0;
	int p;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",ch+1);
		p=0;//清零
		for(int j=1;j<=n;j++)
		{
			if(ch[j]=='C')Map[i][j]=1,p++;//输入同时顺便统计每行1的个数 
			else Map[i][j]=0;
		}
		ans+=flag[--p];//记得找寻（n-1）位
	}
	for(int i=1;i<=n;i++)
	{
		p=0;
		for(int j=1;j<=n;j++)
			if(Map[j][i])p++;
		ans+=flag[--p];
	}//统计每列的巧克力对数
	cout<<ans;
	return 0;
}

```

---

## 作者：Jay_Z (赞：1)

代码可能因为是小白所以有点长。。。不过比较好写，因为大部分重复，CV就行，稍作改动

这个解法没有我看到的其他解法简洁，快速，但是如果新人看我的可能理解更好点吧。。。

本来准备DFS（刚学想练手），写着写着就发现更简单的写法。。。

解法就是计每行与每列的‘C’个数，然后每行每列的个数（>=2的前提下）利用组合公式求解
```cpp
#include <iostream>
#include <cstring> 
using namespace std;
double jiec(int n){  //阶乘函数
	double sum =1;   //double防超
	for(int i = n;i>0;i--){
		sum *= i;
	}
	return sum;
}
int main() {
	int wide;
	double sum = 0,count = 0;  //double防超
	scanf("%d",&wide);        //边长
	char cake[wide+1][wide+1];
	int nu[wide],nu2[wide];   //分别计行与列的个数（有点啰嗦的感觉，
    				应该有优化的方法，但是我比较lazy。。。）
    
	memset(nu,0,sizeof(nu));
	memset(nu2,0,sizeof(nu2));  //初始化为0
	for(int i =0;i<wide;i++){
		scanf("%s",&cake[i]);
	}
	for(int i = 0 ;i<wide;i++){   //遍历每行
		count = 0;
		for(int j = 0;j<wide;j++){
			if(cake[i][j]=='C'){
				count += 1;
			}
		}
		nu[i]=count;             //赋值个数
	}
	for(int i = 0 ;i<wide;i++){   //遍历每行
		count = 0;
		for(int j = 0;j<wide;j++){
			if(cake[j][i]=='C'){
				count += 1;
			}
		}
		nu2[i]=count;          //赋值个数
	}
	for(int i = 0;i<wide;i++){
		if(nu[i]>=2){
			sum += jiec(nu[i])/(2*jiec(nu[i]-2)); 
            						//组合公式求解行
            						（不会请问度娘）
		}
	}
	for(int i = 0;i<wide;i++){
		if(nu2[i]>=2){
			sum += jiec(nu2[i])/(2*jiec(nu2[i]-2));  
            					//组合公式求解列
		}
	}
	printf("%.0f",sum);
	return 0;
}
```


---

## 作者：Pureqyu (赞：0)

  这道题很明显就是求组合数，对于每一行每一列都要求出这一行列的对数，每次都是从行或者列中选择两个C，假设有n行，也就是求C(n,2)这一个答案，而C(n,2)所求答案也就是n * (n - 1) / 2.因此，在进行求解的时候设置两个循环，分别对行和列进行求解，答案也就算出来了。
```
#include <iostream>
#include <cstdio> 
using namespace std;
int n, cnt, sum;
char  maze[102][102];
long long int cal(int x){
	long long a = x;
	return a * (a - 1) / 2;
}
int main(){
	cin >> n;
	for(int i = 0; i < n; i ++){
		scanf("%s",maze[i]);
	}
	for(int i = 0; i < n; i ++){
		for(int j = 0; j < n; j ++){
			if(maze[i][j] == 'C'){
				cnt++;	//计算当前行有多少C
			}
		}
		int temp = cal(cnt);
		sum += temp;
		cnt = 0;
	}
	for(int i = 0; i < n; i ++){
		for(int j = 0; j < n; j ++){
			if(maze[j][i] == 'C'){
				cnt++;   //计算当前列有多少C
			}
		}
		int temp = cal(cnt);
		sum += temp; 
		cnt = 0;
	}
	printf("%d\n",sum);
	return 0;
}
```


---

