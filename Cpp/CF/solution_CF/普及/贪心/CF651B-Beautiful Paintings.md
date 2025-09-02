# Beautiful Paintings

## 题目描述

有n幅画，第i幅画的好看值为a[i]。游客在从一幅画走到更漂亮的一幅画时会很高兴。画可以以任意顺序码放，游客从头至尾走一遍，高兴次数的最大值为c。求c的最大值。

## 说明/提示

在第一个例子中，最佳顺序为：10、20、30、40、50。
在第二个例子中，最佳顺序为：100、200、100、200。

## 样例 #1

### 输入

```
5
20 30 10 50 40
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4
200 100 100 200
```

### 输出

```
2
```

# 题解

## 作者：666DHG (赞：4)

- ### [Blog](https://666DHG.github.io/)

我的思路如下:

1. 读入，**排序**

2. 扫一遍，并于每组的最大值对比，如果大于这组的最大值的话就更新这组的最大值，退出。假如这个值比每一组的最大值都小，则新开一组（可以用
```vector```
来实现）

代码如下：

```cpp
// Time : 497ms
// Memory : 12.00KB
#include <bits/stdc++.h>
using namespace std;

bool flag;
int n,a[1005];
vector <int> V; //记录每组的最大值 

int main()
  {
  	scanf("%d",&n);
  	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
  	sort(a+1,a+1+n); //排序 
  	for (int i=1;i<=n;i++)
  	  {
  	  	flag=false;
  	  	for (int j=0;j<V.size();j++) if (a[i]>V[j]) //与每组最大值对比 
  	  	  {
	  	  	V[j]=a[i]; //更新最大值 
	  	  	flag=true;
	  	  	break;
		  }
		if (!flag) V.push_back(a[i]); //新开一组 
	  }
	return printf("%d",n-V.size())&0; //注释1 
  }
```

注释1 ： 为什么答案是**总数减去组数**？

由题知，**高兴的次数的最大值=总数-不高兴的次数的最小值**

那么我们的目标就由**求高兴的次数的最大值**转成了**求不高兴的次数的最小值**

而且只有在第 $i$ 幅画比第 $i-1$ 幅画小时才会不高兴

先举个例子

假如我现在的
```vector```
数组如下：

```
V[0] = 10
V[1] = 30
V[2] = 5

V.size() = 3
```

那么我只要以下面这种方式来摆画，

![](https://cdn.luogu.com.cn/upload/image_hosting/s2diocos.png)

客人就只会在 $A,B,C$ 处不高兴，因为 $A,B,C$ 一定小于前面的那幅画

其他地方都是高兴的

其实，无论以**什么顺序来摆画，结果都是一样的**

点个赞再走吧 QAQ QwQ

---

## 作者：EuphoricStar (赞：0)

思路：要使游客的高兴次数最大，就要每次都走到比该幅画好看值更大的画。如果当前所在的画好看值已经是最大的，那就从当前好看值最小的画重新摆起。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

int a[1010], cnt[1010], n, res;
bool flag = 1;

int main()
{
    ios::sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i], ++cnt[a[i]];
    while (flag) // 当所有画都看完了就退出循环
    {
        flag = 0;
        // 每次枚举好看值更大的画
        for (int i = 0; i < 1001; ++i)
            if (cnt[i])
            {
                if (flag)
                    ++res;
                else
                    flag = 1;
                --cnt[i];
            }
    }
    cout << res;
    return 0;
}
```


---

## 作者：皮卡丘最萌 (赞：0)

蒟蒻来发一个新的解法：

假设输入中没有相同数字，那么我们可以直接贪心从小到大排序。

但是因为输入中可能出现相同数字，所以直接贪心会产生错误。

例如：20 30 30 20 40 20，直接贪心是20 20 20 30 30 40，结果为2，但是20 30 40 20 30 20的结果更优，结果为3。

所以我们就需要把重复的去掉重新再做，一直到所有数取完。这里有一个简单的方法就是计数排序。

还是举20 30 30 20 40 20，我们首先把所有的数先放进一个数组：

![404](https://cdn.luogu.com.cn/upload/image_hosting/m17m71uh.png)

接下来每次从1到1000扫描一遍，找到非0的点记录其个数，再将其个数减1，直到所有的点都为0是停止。

这样既可以保证取的数是有序的，又可以保证答案最大，~~代码又非常短~~。

我们令数据个数为n，所有数的最大值为m，则此程序的复杂度在所有数相等时达到O(nm)最大,因为这2个数的积最大为1000000，所以不会超时，~~而多数情况下是跑不到这个时间的~~ 。

代码如下：
```pascal
var n,i,s,t,x,sum:longint;
f:array[0..100001] of longint;
begin
readln(n);
for i:=1 to n do
  begin
  read(x); inc(f[x]);    //记录每一个数出现的次数
  end;
while s<n do
  begin
  t:=0;                 //取的数个数归零
  for i:=1 to 1000 do      //枚举每个值的数
    if f[i]>0 then        //如果这种数没有取完
      begin
      inc(t);          //增加取的个数
      dec(f[i]);            //将其个数减一
      end; 
  s:=s+t;            //记录总个数
  sum:=sum+t-1;         //记录高兴次数
  end;
writeln(sum);       //输出结果
end.
```

PS:在CF的数据下，此程序最慢的一个点跑了31ms，可以说是比较快了。

---

## 作者：wzm2007 (赞：0)

	其实只需把结构体排一遍序即可
   	代码如下:

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int beauty;
	bool vis;
}a[1010];
bool cmp(node x,node y)  //结构比较函数
{
	return x.beauty<y.beauty;
}
int n,ans;
void scan()  //用来检查
{
	int num=0,last;
	while(a[num].vis)num++;
	last=a[num].beauty;
	a[num].vis=1;
	for(int i=num+1;i<n;i++)  //扫一遍
		if(a[i].beauty>last&&!a[i].vis)
		{
			ans++;
			last=a[i].beauty;
			a[i].vis=1;
		}
}
bool check()  //检查是否全部看完
{
	bool f=0;
	for(int i=0;i<n;i++)
		if(!a[i].vis)f=1;
	return f;
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)scanf("%d",&a[i].beauty);  //读入
	sort(a,a+n,cmp);  //排序
	while(check())scan();  //如果没走完，继续扫描
	cout<<ans;  //输出
	return 0;  //完美结束
}
```


------------
###### 求通过

---

## 作者：heziqi (赞：0)

# 此题用dfs就可以了！

# 但是光用它第六个点过不了！

# 它会TLE！！！

# 不过骗点分还是可以的！

#  ~~TLE代码~~：
```
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
int n,a[1005],vis[1005],cnt,ans;
void dfs(int s){
    vis[s]=1;
    int flag=0;
    for(int i=1;i<=n;i++){
        if(vis[i]==0){
            flag=1;
            vis[i]=1;
            int t=cnt;
            if(a[i]>a[s]&&s!=0)cnt++;
            dfs(i);
            cnt=t;
            vis[i]=0;
        }
    }
    if(flag==0){
        ans=max(ans,cnt);
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    dfs(0);
    cout<<ans;
    return 0;
}
```

# 不过如果想AC，

###### ~~ _this：_ ~~
```
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
int n,a[1005],vis[1005],cnt,ans;
void dfs(int s){
    vis[s]=1;
    int flag=0,f=0;
    for(int i=s+1;i<=n;i++){
        if(vis[i]==0){
            flag=1;
            if(a[i]>a[s]){
            	cnt++;
            	f=1;
            	vis[i]=1;
            	dfs(i);
            	break;
            }
        }
    }
    if(flag==0){
        ans=max(ans,cnt);
    }
    if(f==0){
    	for(int i=1;i<=n;i++){
    		if(vis[i]==0){
    			vis[i]=1;
    			dfs(i);
    			break;
            }
        }
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+1+n);
    dfs(1);
    cout<<ans;
    return 0;
}
```

# 说白了+个sort就行！

---

