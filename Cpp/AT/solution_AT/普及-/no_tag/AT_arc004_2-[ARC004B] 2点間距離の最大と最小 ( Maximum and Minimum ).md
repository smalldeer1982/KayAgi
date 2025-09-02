# [ARC004B] 2点間距離の最大と最小 ( Maximum and Minimum )

## 题目描述

间距最大值和最小值。( Maximum and Minimum )

平面上有n + 1个点，分别从0到n编号.
虽然不知道各点位置，但对于0以上且小于n的整数i，第i点和第i+1点的距离为d_i。
请求出从第0个点和第n个点的距离能够取到的值的最大值和最小值。

# 题解

## 作者：Doveqise (赞：4)

这道题我看题解区讲的都很谜  
所以我来发图解释一下  
如图（SketchPad画的有点丑）  
![AT185题解图](https://cdn.luogu.com.cn/upload/pic/61695.png)   
现在有$5$个点 ①②③④⑤，相邻两点距离分别为$1,2,3,4,5$，  
我们要求①~⑤的最大距离，就是把他们的距离加起来  
那么最小距离呢？  
如果最长的边长度$≤$其余边长度之和，  
我们看一下图二，就是这样，所以最小距离为$0$；  
如果最长的边的长度$>$其余边长度之和，  
我们看一下图三，这里4和5的距离改成了$8$，  
所以最小距离就是最长的边的长度$-$其余边长度之和，  
即$8-1-2-3=2$；  
接下来贴代码↓  
```cpp
#include<bits/stdc++.h>
using namespace std;
signed main()
{
    int n, tot=0, maxx=0;
    scanf("%d",&n);
    for (int i=1,x; i<=n; i++)
    {
        scanf("%d",&x);
        tot+=x; 
        maxx=max(maxx, x);
    }
    printf("%d\n",tot); 
    tot-=maxx;
    if (tot>=maxx)
        puts("0");
    else 
        printf("%d\n",maxx-tot);
    return 0;
}
```

---

## 作者：インデックス (赞：3)

### ~~这道紫题有点水~~

### MAX值=距离之和

### MIN值=最长距离-其他距离和
```
#pragma GCC optimize (2)//O2
#include<bits/stdc++.h>//万能头文件
using namespace std;
 
inline int read()//定义一波函数啊
{
    int x=0,f=1;char ch=getchar();
    for (;ch<'0'||ch>'9';ch=getchar()) if (ch=='-') f=-1;
    for (;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+ch-'0';
    return x*f;//函数返回值
}
 
int main()//主函数开始
{
    int n=read(), sum=0, mx=0;
    for (int i=1; i<=n; i++)
    {
    	int x=read();
    	sum+=x; mx=max(mx, x);
    }
    printf("%d\n",sum); sum-=mx;
    if (sum>=mx) printf("0\n");//两种情况的判断
    	else printf("%d\n",mx-sum);
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：2)

### Update
2022.5.15 更新了一个笔误，感谢 @[\_LHM](https://www.luogu.com.cn/user/613124)

水题，现已降橙。
#### 思路：
对于本题，各点位置不知道。对于最大距离，我们可以把它想象成一条链，所以最大值即为所有点的距离之和 $sum$。对于最小值，我们就是用最大值 $maxn$ 减去其它边之和，这肯定是最大的。即用第一问的结果 $sum$ 减最大值 $maxn$ 后，答案为 $\max\{maxn-sum,0\}$。因为如果 $maxn-sum<0$ 时，一定能构造出 $0$ 与 $n$ 两点重合的情况。（本题最优解，可以不用数组）
### AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,sum,maxn,a;
int main(){
    scanf("%d%d",&n,&maxn);
    sum=maxn;
    for(int i=2;i<=n;i++){
        scanf("%d",&a);
        sum+=a;
        maxn=max(maxn,a);
    }
    printf("%d\n",sum);
    sum-=maxn;
    printf("%d\n",max(maxn-sum,0));
    return 0;
}
```

---

## 作者：鸢一折远 (赞：2)

这题有点水啊==

对于最长，显然就是所有距离加起来；

对于最短，我们找出最长的距离，以及其他距离的和，当最长距离大于其他距离和的时候，就算把两个距离重合了0与n也够不到，答案即为最长距离-其他距离和；当最长距离小于时，你显然可以吧两个距离a,b看成一个更短的距离c(|a-b|<=c<=a+b)，所以一定能构造出0与n重合的情况，答案为0；


------------
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#define F(i,s,t) for(int i=s;i<=t;++i)
using namespace std;
int n,a[2333];

int main(){
	scanf("%d",&n);
	int maxx=0,sum=0;
	F(i,1,n){
		scanf("%d",a+i);
		maxx=max(maxx,a[i]);
		sum+=a[i];
	}
	printf("%d\n",sum);
	sum-=maxx;
	if(sum>maxx) printf("%d\n",0);
	else printf("%d\n",maxx-sum);
	return 0;
}
```

---

## 作者：CmsMartin (赞：1)

# 题解

## 思路

对于求最大值时只需求出所有点距离的和，记为 $sum$ , 输出 $sum$

当求最小值时，只需用 $sum - max$ ( $max$ 为最大值)，注意这里有一个细节：当 $max \leq sum$ 时，输出 $0$ ,因为此时必定能构造出 $n$ 与 $0$  重合


## 标程

```Java

import java.util.Scanner; 
 
public class Main {
    static int n , tot , maxx;
    public static void main(String[] args) {
        Scanner Scan = new Scanner(System.in);
        n = Scan.nextInt();
        for(int i = 1;i <= n;i++) {
            int temp;
            temp = Scan.nextInt();
            tot += temp;
            if(temp >= maxx) maxx = temp;
        }
        System.out.println(tot);
        tot -= maxx;
        if(tot >= maxx) {
            System.out.println("0");
        }
        else  System.out.println(maxx - tot);
        Scan.close();
    }
}
```

```cpp

#include <bits/stdc++.h>
using namespace std;

int n , sum , maxx , tot;

int main() {
	scanf("%d" ,&n);
	while(n--) {
		int temp;
		scanf("%d" ,&temp);
		tot += temp;
		maxx = max(maxx , temp);
	}
	printf("%d\n" ,tot);
	tot -= maxx;
	if(tot >= maxx) {
		puts("0");
	}
	else printf("%d" ,maxx - tot);
	return 0;
}

```

---

## 作者：_Hero_ (赞：1)

# 分析
从题目可知，要求出从 第 $0$ 个点和第 $n$ 个点的距离 能够取到的值的最大值和最小值，最大值就是从 第 $0$ 个数到第 $n$ 个数的和 ，最小值就是 最长间距 $-$ 其他间距长度之和 。不过如果 最间距长度$≤$其余间距长度之和 ，那么最小值为 $0$ ，所以我们可以用``` if ```在加一个判断就行啦。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
int w,a[502],n,s;
int main()
{cin>>n;
for(int i=0;i<n;i++)
{
	cin>>a[i];
	s=s+a[i];//求和
}
sort(a,a+n);//排序求最长间距
cout<<s<<endl;
w=a[n-1];
s=s-w;
if(s>=w)cout<<0<<endl;//判断
else cout<<w-s<<endl;
   return 0;
}
```


---

