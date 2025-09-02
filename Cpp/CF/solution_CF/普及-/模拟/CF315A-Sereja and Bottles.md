# Sereja and Bottles

## 题目描述

Sereja and his friends went to a picnic. The guys had $ n $ soda bottles just for it. Sereja forgot the bottle opener as usual, so the guys had to come up with another way to open bottles.

Sereja knows that the $ i $ -th bottle is from brand $ a_{i} $ , besides, you can use it to open other bottles of brand $ b_{i} $ . You can use one bottle to open multiple other bottles. Sereja can open bottle with opened bottle or closed bottle.

Knowing this, Sereja wants to find out the number of bottles they've got that they won't be able to open in any way. Help him and find this number.

## 样例 #1

### 输入

```
4
1 1
2 2
3 3
4 4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4
1 2
2 3
3 4
4 1
```

### 输出

```
0
```

# 题解

## 作者：封禁用户 (赞：3)

题目传送>>[CF315A](https://www.luogu.com.cn/problem/CF315A)  
### 题意简述：  
给定 $n$ 个瓶子，$a_i$ 类的瓶子可以打开 $b_i$ 类的瓶子，求最终无法打开的瓶子数。  
### 题目分析:  
根据题意直接进行暴力枚举，检查可被打开的瓶子数，再用瓶子总数减去可被打开的瓶子数即可得到答案。但是需要注意的是自己不能打开自己，另外要对已被打开的瓶子进行标记，下次再遇到打开此瓶子时就不作计数。（我自己就被这个坑了一会）  
### Code:  
```cpp
#include <iostream>
#include <cstring> 
using namespace std;
struct bottle   //结构体存a类瓶子和b类瓶子
{
	int a, b;
} p[101];
int w[101];   //开数组标记第i个瓶子是否被开过
int main()
{
	ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
	int n;   //定义瓶子总数
	int k = 0;   //定义已开的瓶子数
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> p[i].a >> p[i].b;
	}
	memset(w, 0, sizeof(w));   //标记数组初始化
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (j != i && p[i].b == p[j].a && w[j] == 0)
			{
				k++;   //记录已被开瓶子数
				w[j] = 1;   //标记该瓶子已被开
			}
		}
	}
	cout << n - k;   //瓶子总数减去可被打开的瓶子数即可得到答案
	return 0;   //结束整个程序
}
```
### 结果（未吸氧）:  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/ornc6s9e.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：LuffyLuo (赞：2)

这道题有点难。

大家先看一下题目，题目大意就是说给定 $n$ 个瓶子，$a$ 类的瓶子可以用来打开 $b$ 类的瓶子，求最终无法打开的瓶子数。

#### 思路：
这道题纯属是枚举好吧，循环找就是了，并且找一个变量来储存打不开的个数（那么首先就要把它认为所有都打不开），用两个循环就行了，一个模拟瓶子，一个模拟瓶盖，如果他们并不是在一起的，而且刚好对的上，那么就将这个变量减去一。

贴上我的代码：
```cpp
#include<bits/stdc++.h>
const int MAX=110000;
using namespace std;
int a[MAX],b[MAX];//一个是盖子，一个是瓶子 
int main(){//主函数 
    int n,ans,i,j;//ans为无法打开的瓶子数 
    scanf("%d",&n);
    ans=n;
    for(i=1;i<=n;i++)
        scanf("%d %d",&a[i],&b[i]);
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            if(a[i]==b[j]&&i!=j){
                ans--;
                break; 
            }
    printf("%d",ans);
    return 0;
}
```
//不用说谢谢，不因客套，只因能见您的笑容，以及您电脑上的 AC，您已经回报。

//祝大家信息学越来越棒哦！

---

## 作者：chino_33 (赞：1)

注明：此题或因恶意评分被注明为紫题，实际难度为红题
```cpp
#include<iostream>
using namespace std;
int main()
{
    int n,ans,a[23333],b[23333];
    cin>>n;
    ans=n;
    for(int i=1;i<=n;i++)
        cin>>a[i]>>b[i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(a[i]==b[j] && i!=j)
            {
                ans--;
                break;
            }
        }
    cout<<ans;
    return 0;
}
```
上代码。
数据简单所以直接暴力就可以了
主要是提交题解希望把难度改回来
【望通过】

---

## 作者：违规用户名2REHD80TR (赞：1)

~~很水的一道题啊!~~
```
这题显然是自己不能开自己，那就统计一下，一次就令f为1，多次就令f为2
如果f为2，无论如何都可以做到打开（即便自己不能开自己），大家想一下
其次如果f为1，只要不是自己开自己的那种都可以打开
```
------------
```
#include<stdio.h>
int n,k=0,a[1001],b[1001],f[1001];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
		if(f[b[i]]==2) continue;
		f[b[i]]++;
	}
	for(int i=1;i<=n;i++) if(a[i]==b[i]&&f[a[i]]==1||f[a[i]]==0) k++;
	printf("%d",k);
}
```

---

## 作者：Lish_Xizse (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF315A)

这是一道简单明了的模拟题。


------------
### 分析与思路

其实这道题简单化以后就是让我们求在两数编号不相等的情况下有多少对数字是相等的。用总数减去对数就可以了。

我们需要利双重循环来解决这道题。一边扫描瓶子，另一边扫描盖子，**遇到数字相等的**且**编号不相等就将计数器累加一**（因为自己不能开自己），最后用总数减去对数。暴力就能过。



------------
### 完整 ```AC``` 代码：

```
#include<iostream>
using namespace std;
int n,a[110],b[110];
int main(){
    cin >> n;
    int sum=0;
    for(int i=1;i<=n;i++)cin >> a[i] >> b[i];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i]==b[j]&&i!=j){
                sum++;
                break;
            }
        }
    }
    cout << n-sum << endl;
    return 0;
}
```


---

## 作者：hswfwkj_ (赞：0)

题目传送门：
[CF315A](https://www.luogu.com.cn/problem/CF315A)

很简单的一道题,$n\le100$，看到这样的数据范围，算法已经呼之欲出：
### 枚举！
讲一下枚举的思路：
用两层循环，第一层代表当前瓶子，第二层代表要打开的瓶子，如果当前拿的瓶子能打开要打开的瓶子，就标记一下。

最后一个循环扫一遍，统计不能打开的瓶子数量即可。

贴上代码：
```cpp
#include<iostream>
using namespace std;
int i,j,n,a[201],b[201],c[201],ans;
int main(){
	cin>>n;
	for(i=1;i<=n;i++)
		cin>>a[i]>>b[i];
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++){
			if(j==i)continue;
			if(a[j]==b[i])
				c[j]=1;
		}
	for(i=1;i<=n;i++)
		if(!c[i])
			ans++;
	cout<<ans;
	return 0;
}
```
很通俗易懂，我想都不需要注释了。
当前最优解：
![](https://cdn.luogu.com.cn/upload/image_hosting/14uoxnxy.png)


---

## 作者：shAdomOvO (赞：0)

### 分析
这题其实很简单，~~可我却做了很久~~.

问你有哪些瓶子不能打开，那我们只要开两个数组。

 $A$ 数组存需要打开的, $B$ 数组存可以打开的。

但是，我们需要想到一点，那就是不可以自己打开自己，所以可以再用一个数组 $C$ 特判。

### 关于特判
如果 $A$ 值等于一，且 $C$ 值也为一，那么说明只有一个重复的，很显然不能打开。那么答案加一

### 下面是代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1010],b[1010],c[1010],n,i,m,j,ans=0,k;
int main(){
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>k>>m;
		a[k]++;//需要打开的 
		b[m]++;//可以打开的 
		if(k==m)c[k]++;//如果重复，需要特判 
	}
	for(j=1;j<=1000;j++){
		if(c[j]==1&&b[j]==1){//c不等于0，说明有重复，许要两个以上的瓶子才能打开 
			ans++;
		}
		else{
			if(a[j]>=1&&b[j]==0)ans+=a[j];
		}
	}
	cout<<ans;//完结撒花！！！
}
```



---

