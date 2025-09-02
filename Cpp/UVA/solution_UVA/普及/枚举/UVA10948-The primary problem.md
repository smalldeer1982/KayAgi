# The primary problem

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=21&page=show_problem&problem=1889

[PDF](https://uva.onlinejudge.org/external/109/p10948.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10948/e8db1ede82953ce1670162c4cb5dde5e02f35076.png)

## 样例 #1

### 输入

```
4
5
6
7
9
10
11
0```

### 输出

```
4:
2+2
5:
2+3
6:
3+3
7:
2+5
9:
2+7
10:
3+7
11:
NO WAY!```

# 题解

## 作者：封禁用户 (赞：4)

### 前言

[前置](https://www.luogu.com.cn/problem/P3383)

[cnblog](https://www.cnblogs.com/CM-0728/p/14406827.html)

### $\sf{Solution}$


既然有了 $n$ ，那找出 $a$ 和 $b$ 就只要枚举 $a$ 的范围 $1\sim n$，判断 $a$ 和 $n-a$ 是否为质数.

因为 $a$ 和 $b$ 都不为负数，所以可以缩小枚举范围为 $1\sim \dfrac{n}{2}$ .

至于判质数，相信欧拉筛能解决问题.

[欧拉筛相关](https://www.luogu.com.cn/blog/CM0/solution-p3912)（~~请忽略中二部分~~

### $\sf{Code}$

```cpp
#include<iostream>
using namespace std;
int n,ans,prime[5000005];
bool visit[10000005];
int main()
{
	ios::sync_with_stdio(false);
	visit[1]=true;//初始化
	for(int i=2;i<=10000000;++i)
	{
		if(!visit[i])
			prime[++ans]=i;
		for(int j=1;prime[j]*i<=10000000&&j<=ans;++j)
		{
			visit[i*prime[j]]=true;
			if(!(i%prime[j]))
				break;			
		}
	}//欧拉筛
	while(cin>>n&&n!=0)
	{
		bool flag=false;//别忘了初始化
		cout<<n<<":\n";
		for(int i=2; i<=n/2; ++i)
		{
			int a=i,b=n-i;
			if(!visit[a]&&!visit[b])
			{
				cout<<a<<"+"<<b<<"\n";
				flag=true;//有解标记
				break;
			}
		}
		if(!flag)
			cout<<"NO WAY!\n";//无解
	}
	return 0;
}
```

---

## 作者：star_looker (赞：0)

又是一道$H_2O$题。

思路：全循环输入一遍，再用暴力逐个判断，最后输出。

CODE：

```cpp
#include<cstdio>
bool is_prime(int n){//判断指数函数
	if(n<2) return false;//特判
	for(int i=2;i<n;i++){//普通判断
		if(n%i==0) return false;//要保持1和数本身不包含在内
	}return true;//别的已经跳转掉了
}
int main(){
	int n;bool flag=false;//变量
	while(1){//循环输入输出
		flag=false;//清零
		scanf("%d",&n);
		if(n==0) return 0;//终止条件
		for(int i=2;i<=n/2;i++){
			if(is_prime(i)&&is_prime(n-i)){//暴力
				printf("%d:\n%d+%d\n",n,i,n-i);//输出，注意格式
				flag=true;//为了后面输出
				break;//这样一来一定最小
			}
		}if(!flag) printf("%d:\nNO WAY!\n",n);//没有输出“NO WAY”
	} 
   return 0;
}
```


---

## 作者：Water_Cows (赞：0)

这题就是一个欧拉筛 + 暴力枚举。

- #### 欧拉筛

  - 首先讲一下**埃氏筛**（因为是欧拉筛的基础）
    
    埃氏筛法的基本思想 ：从2开始，将每个质数的倍数都标记成合数，以达到筛选素数的目的。
  
  - 之后就是**欧拉筛**
    
    欧拉筛法的基本思想 ：在埃氏筛法的基础上，让每个合数只被它的**最小质因子**筛选一次，以达到不重复的目的。（~~简单吧~~）

  - 上代码：
  
  ```cpp
  int pd[N], ans[N], cnt; // N是你要筛选的质数的数量
  inline void prime()
  {
      pd[1]=1; // 每日初始化心情好
      for(int i=1; i<=N; i++)
      {
          if(!pd[i]) ans[++cnt]=i; // 如果以前没有被标记过，那就是质数
          for(int j=1; j<=cnt; j++)
          {
              if(ans[j]*i>N) break; // 筛出来的质数如果超出了要筛的范围，那么就退出
              pd[ans[j]*i]=1; // 否则就标记为不是质数
              if(i%ans[j]==0) break; // * 最重要的一步！如果找到了最小质因子，就退出。这完美的做到了线性筛
          }
      }
  }
  ```
讲到这里差不多结束了，其他就是暴力枚举的事情了。

$Code:$

```cpp
#include <cstdio>
using namespace std;

int n;

const int N = 10000000 + 10;

int pd[N], prime[N];
int cnt;
inline void diprime()
{
    pd[0] = pd[1] = 1;
    for(int i=2; i<=N; i++)
    {
        if(!pd[i]) prime[++cnt]=i;
        for(int j=1; j<=cnt; j++)
        {
            if(prime[j] * i > N) break;
            pd[prime[j] * i] = 1;
            if(i%prime[j] == 0) break;
        }
    }
    return ;
}

int main()
{
    diprime();
    while(scanf("%d", &n))
    {
        int flag = 0;

        if(n == 0) break;
        printf("%d:\n", n);
        for(int i=1; i<=cnt; i++)
        {
            int p1 = prime[i];
            int p2 = n - prime[i];
            if(p1 > p2) break;
            if(pd[p2]) continue;
            
            printf("%d+%d\n", p1, p2);
            flag = 1;
            break;
        }
        
        if(!flag) puts("NO WAY!");
    }
}
```


---

