# Two Buttons

## 题目描述

Vasya has found a strange device. On the front panel of a device there are: a red button, a blue button and a display showing some positive integer. After clicking the red button, device multiplies the displayed number by two. After clicking the blue button, device subtracts one from the number on the display. If at some point the number stops being positive, the device breaks down. The display can show arbitrarily large numbers. Initially, the display shows number $ n $ .

Bob wants to get number $ m $ on the display. What minimum number of clicks he has to make in order to achieve this result?

## 说明/提示

In the first example you need to push the blue button once, and then push the red button once.

In the second example, doubling the number is unnecessary, so we need to push the blue button nine times.

## 样例 #1

### 输入

```
4 6
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10 1
```

### 输出

```
9
```

# 题解

## 作者：Soshine_溯闪 (赞：17)

我**第一次**传题解。    
~~其实找到题的题解，我传了7次，都没过。~~  
找到题跟 [P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135) 很像，大家可以尝试做一下那题。
# 整体思路  
1.这道题是很经典~~水~~的 bfs 题。  
2.因为有两个按钮，所以while里有考虑了两种情况（ +1 和 *2 ）。  
3.vis 要 memset 成 -1 ，至于为什么，就请各位大佬思考思考了。  
4.具体看程序。

## 直接上程序
```cpp
#include <iostream>
#include <queue>
#include <cstring>		//头文件 
using namespace std;
int n,m,vis[10005];		//vis[i]表示变成i需要的最少按按钮次数 
int bfs(){
	queue<int> q;		//定义队列 
	q.push(n);		//初始化队列 （放n） 
	vis[n]=0;		//初始化vis[n] 
	while(!q.empty()){		//正片开始 
		int front=q.front();		//将q.front存起来 
		q.pop();				//因为要出队列 
		if(front==m) 	//可以返回 
			return vis[front];		//返回 
		int nxt=front-1;		//一种情况 -1 
		if(nxt>=0&&nxt<=10005&&vis[nxt]==-1){		//判断 
			vis[nxt]=vis[front]+1;
			q.push(nxt);
		}
		nxt=front*2; 		//一种情况 *2 
		if(nxt>=0&&nxt<=10005&&vis[nxt]==-1){		//判断 
			vis[nxt]=vis[front]+1;
			q.push(nxt);
		}
	}
}
int main(){
	memset(vis,-1,sizeof(vis));		//将vis初始化为-1 
	cin>>n>>m;
	cout<<bfs()<<endl;		//输出 
	return 0;		//AC 
}
```
别忘了我问的问题。  
求管理员通过。    
也求大佬们点个赞。  
我是五年级学生，才学编程2年，你们的赞是我最大的鼓励！

---

## 作者：JRzyh (赞：9)

看比所有题解都短，所以写写


------------
显然，如果 $m<n$，只能操作二，一点点减，答案为 $n-m$。

更显然，$m=n$ 时答案为 $0$。

现在来看看 $m>n$ 时，因为要尽快增大 $n$ 方法肯定是若干个乘二，一个减一，再若干个乘二，再一个减一，以此类推。

问题是什么时候减这个一。

很多题解开始拆二进制了其实没有必要。

正难则反。

我们将问题转化为：每次将 $m$ 除以 $2$ 或者加 $1$，多少次能变成 $n$。 

立刻明朗了，$m$ 是偶数时除以 $2$ ,不是时加 $1$。

还有个小问题，除以二之后可能会变得小于 $n$，这之后不能再除了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main()
{
	cin>>n>>m;
	if(m<=n)
	{
		cout<<n-m;
		return 0;
	}
	else
	{
		int ans=0;
		while(m!=n)
		{
			if(m%2==0&&m>=n)m/=2;
			else m++;
			ans++;
		}
		cout<<ans;
	}
    return 0;
}

```



---

## 作者：infinities (赞：9)

本蒟蒻不才，献上模拟题解一篇

首先，这题我开始把它想的太简单了，以至于WA了无数次，这是我最开始的思路，十分简单（不是正解，请稍后）：
- 首先，如果n>=m，就输出n-m

- 其次，如果n<m，就先不停乘以2，知道n大于等于m为止

- 再输出乘了几次+现在的n-m

这是代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,m,ans=0;
    cin>>n>>m;
    if(n>=m){
        cout<<n-m;
        return 0;
    }
    else{
        while(m>n){
            n*=2;
            ans++;
        }
        if(n==m){
            cout<<ans;
            return 0;
        }else{
            cout<<ans+n-m;
            return 0;
        }
    }//注释就不加了，看后面
}
```
然后再讲讲正解思路：

- 最重要的一点：n的减1可以在乘二的过程中进行

- 而众所周知，这个减1一直累积到后面就会变成2的X次方（X>=0）

- 一开始和上面的思路差不多，就是记录一下乘2的次数

- 然后记录n-m的数值，从原先n乘2的次数向1枚举

- 再然后，n-m的数值能减去2的i次方就使劲减,别忘了计入步骤数

code:
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int main(){
    /*freopen(...);
      freopen(...);(懒，不写了)*/
    int n,m,ans=0,z,k=0,l=0;//定义
    cin>>n>>m;//输入
    if(n>=m){
        cout<<n-m;
        return 0;
    }//进行特判
    else{
        while(m>n){
            n*=2;
            ans++;
            l++;
        }//不断乘2，思路说了这里不讲太多
        l=min(13,l);
  //因为8192是10000以内最大的2的幂次方，而8192是2的13次方，所以对13取min（后来一想取min似乎多余了）
        if(n==m){
            cout<<ans;
            return 0;
        }//如果恰好就是，直接输出
        else{//不然就进行操作
            ans+=n-m,z=n-m;//记录n-m，计数器加上
            for(int i=l;i>=1;i--){
                k=pow(2,i);//2的幂次方
                while(z>=k){//能减就使劲减，反正不亏
                    z-=k,
                    ans-=k,ans++;//操作数减去2的幂次方之后还要再加一，因为这也是个操作
                }
            }
            cout<<ans;//最后输出
            return 0;
        }
    }
}
```
最后，本蒟蒻自己测了几组大点的数据（4000左右），结果惊讶地发现本蒟蒻~~瞎~~写的代码竟然比楼上大佬写的搜索和DP还快！

---

## 作者：きりと (赞：5)

**[题目传送门](https://www.luogu.com.cn/problem/CF520B)**

### 题目大意

见中文翻译

### 解题思路

拿到题后看了一眼数据范围，以为是一个比较简单的动规，然后发现动规思路稍微有点麻烦，于是打算当做思维题做。

我们可以设我们做了①操作 $x$ 次，做了②操作 $y$ 次，则有：$m=n*2^x-2^{a[1]}-2^{a[2]}-...-2^{a[y]},0≤a[i]≤x$ 。

那么这题的思路就很简单了，先把 $n$ 一直乘 $2$ ，直到 $n≥m$ ，然后记录 $n-m$ 的值和 乘 $2$ 的次数 $x$，然后从 $2^x$ 到 $2^0$ 枚举要被减掉的，第二次操作得到的数，能减则减即可。

### Code

细节有点小多，交了 $2,3$ 发才过呜呜呜。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
    int n,m;
    cin>>n>>m;
    if(n>m)
    {
        cout<<n-m<<endl;
        return 0;
    }
    int cnt=0;
    while(n<m)
    {
        n*=2;
        cnt++;      //cnt表示n乘2的次数
    }
    int x=n-m,ans=cnt;
    for(int i=cnt;i>=0&&x>0;i--)
    {
        if(x>=(1<<i))
        {
            x-=1<<i;
            ans++;
            i++;         //可能一个数会被减好几次，也就是多次-1操作连续进行
        }
    }
    cout<<ans<<endl;
    return 0;
}

```



---

## 作者：TLMPEX (赞：3)

思路：用BFS来解决，主要思路见代码。

```c
#include<bits/stdc++.h>
using namespace std;
int n,m,vis[10001];//vis数组表示到哪一个点需要按几次按钮
int bfs(){
	queue<int> q;
	q.push(n);
	vis[n]=0;//表示到n这个点要按0次
	while(!q.empty()){
		int l=q.front();//取队首元素
		q.pop();//出队列
		if(l==m)return vis[m];//如果到达了目的地，则返回到目的地的按的次数
		int r=l-1;//把r置为上一个点减一
		if(r>=0&&r<=10000&&vis[r]==-1){//如果r在范围以内且没有到过r这个点，则把r入队列，并且把按到这里的次数置为按到上一个点的次数加一
			q.push(r);
			vis[r]=vis[l]+1;
		}
		r=l*2;//把r置为上一个点乘二
		if(r>=0&&r<=10000&&vis[r]==-1){//如果r在范围以内且没有到过r这个点，则把r入队列，并且把按到这里的次数置为按到上一个点的次数加一
			q.push(r);
			vis[r]=vis[l]+1;
		}
	}
}
int main(){
	memset(vis,-1,sizeof(vis));//初始化
	cin>>n>>m;
	cout<<bfs();
}
```


---

## 作者：StupidSeven (赞：1)

## Subject
[题目链接](https://www.luogu.com.cn/problem/CF520B)

## Analysis
考虑BFS，不断拓展，只要原来拓展过就不拓展，不符合条件也不拓展，代码比较好写

## Code
```cpp
#include<map>
#include<ctime>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define M 1000010	
inline int Readint(void){
    int s=0,f=1;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){s=s*10+c-48;c=getchar();}
    return s*f;
}
int n,m;
int dep[M];
bool used[M];
void Bfs(int n,int m){
	queue<int> Q;
	used[n]=true;
	Q.push(n);
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		if(x==m){
			printf("%d\n",dep[x]);
			exit(0);
		}
		if(x*2>=0&&x*2<=10005&&used[x*2]==0){
			dep[x*2]=dep[x]+1;
			used[x*2]=true;
			Q.push(x*2);
		}
		if(x-1>=0&&x-1<=10005&&used[x-1]==0){
			dep[x-1]=dep[x]+1;
			used[x-1]=true;
			Q.push(x-1);
		}
	}
	return;
}
signed main(void){
	n=Readint();m=Readint();
	Bfs(n,m);
	return 0;
}
```

---

## 作者：洛白の纸 (赞：1)

## **这个题其实无脑dp可以过。**
#### 

------------
就是说对于**每一个数**，他都可以更新他的**2倍**或者是他的**下一个数**。
    但是这样**做一次**的话你是得不到**最优解**的
。
所以看一眼数据规模，你就可以**多做几次**。这样有基本上百分之百的概率。


------------
// _一般的话500次就够了，但我试了试，50次也可以，你要是在不放心5000次也是可以的。还有数组记得开大点，莫名会炸。有大佬知道的话，告诉一声。。。。。_ 
```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[8002000];
int main() {
	int m,n;
	cin>>n>>m;
	if(m<=n) {
		cout<<n-m;
		return 0;
	} else {memset(dp,63,sizeof(dp));
	dp[n]=0;
	int t=5000;
	for(int i=n-1; i>=1; i--)dp[i]=dp[i+1]+1;
	while(t--)
	{    for(register int i=1; i<=m+10; i++) {
         dp[i*2]=min(dp[i*2],dp[i]+1);
         dp[i-1]=min(dp[i-1],dp[i]+1);
		}
	}
		
	}
	cout<<dp[m];
	return 0;
}
```
管理大大求过。。。。本弱弱尽力了qwq，，，，，，，，


---

## 作者：cold_cold (赞：1)

贪心的思想：其实如果m比n大 ，n肯定有*2，问题就是先减再乘还是先乘再减。

但是反过来推，如果m是奇数，一定是减一造成的，如果是偶数，更快的办法是*2造成的。就这么循环做下去直到遇到m=n。

[思路来自](https://blog.csdn.net/u014787301/article/details/44161563)

```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
using namespace std;
int n,m,all=0;
int main()
{
	scanf("%d%d",&n,&m);
	while(n<m)
	{
		if(m%2)
			m++;
		else
			m/=2;
		all++;
	}
	printf("%d",all+n-m);
	return 0;
}
```

---

## 作者：Mysterious_Cat (赞：0)

### 题目大意：将$n$通过操作$*2$或$-1$变成$m$，问最少需要几次操作。
### 题目思路：从$n$开始BFS，每次数$i$弹出队列时将$i*2$和$i-1$压入队列，增加$flag$数组判重和边界特判即可。  
### Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

bool flag[100005];

queue<int> q;

int main()
{
    int n, m;
    cin >> n >> m;
    q.push(n);
    flag[n] = true;
    int step = 0;
    while(!q.empty())
    {
        int len = q.size();
        for(int i = 1; i <= len; i++)
        {
            int tmp = q.front();
            q.pop();
            if(tmp == m)
            {
                printf("%d", step);
                return 0;
            }
            if(tmp <= m * 2 && !flag[tmp * 2]) q.push(tmp * 2), flag[tmp * 2] = true;
            if(tmp >= 1 && !flag[tmp - 1]) q.push(tmp - 1), flag[tmp - 1] = true;
        }
        step++;
    }
    
    return 0;
}
```


---

## 作者：Tarensev (赞：0)

## 这道题可以用bfs来做：

思路不难，可以把它看成迷宫，当你在第$i$格时，就可以走到第$i-1$格或$2i$格。

当然需要考虑边界，不然会造成死循环。

当我们发现走到第$0$格的时候，你不能再翻倍了；

走到第$3m$格的时候，就只能往回走，所以就应该停止翻倍。

华丽丽的代码

------------
```
#include<cstdio>
using namespace std;
int q[40004],vis[40004],step[40004];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	if(n>=m)
	{
		printf("%d\n",n-m);
		return 0;
	}//其实这是一个剪枝，因为n>=m时只能往回走，不然会越走越远
	int l=1,r=1;
	q[1]=n;
	vis[n]=1;
	step[n]=0;
	while(l<=r)
	{
		int p=q[l++];	
		if(p==m)//如果到达就输出
		{
			printf("%d\n",step[p]);
			break;
		}
		if((p-1>=0)&&(!(vis[p-1])))//考虑蓝色按钮
		{
			q[++r]=p-1;
			step[p-1]=step[p]+1;
			vis[p-1]=1;
		}
		if((2*p<=3*m)&&(!(vis[2*p])))//考虑红色按钮
		{
			q[++r]=2*p;
			step[2*p]=step[p]+1;
			vis[2*p]=1;
		}
	}
	return 0;
}
```

---

