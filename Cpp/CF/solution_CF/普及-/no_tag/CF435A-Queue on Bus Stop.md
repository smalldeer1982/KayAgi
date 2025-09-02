# Queue on Bus Stop

## 题目描述

It's that time of the year when the Russians flood their countryside summer cottages (dachas) and the bus stop has a lot of people. People rarely go to the dacha on their own, it's usually a group, so the people stand in queue by groups.

The bus stop queue has $ n $ groups of people. The $ i $ -th group from the beginning has $ a_{i} $ people. Every $ 30 $ minutes an empty bus arrives at the bus stop, it can carry at most $ m $ people. Naturally, the people from the first group enter the bus first. Then go the people from the second group and so on. Note that the order of groups in the queue never changes. Moreover, if some group cannot fit all of its members into the current bus, it waits for the next bus together with other groups standing after it in the queue.

Your task is to determine how many buses is needed to transport all $ n $ groups to the dacha countryside.

## 样例 #1

### 输入

```
4 3
2 3 2 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 4
1 2 1
```

### 输出

```
1
```

# 题解

## 作者：伟大的王夫子 (赞：3)

先宣传一下[我的博客](https://www.luogu.com.cn/blog/I-AK-IOI/)

其实这题本身只有红题难度

因为小组的顺序不能改变，所以一个一个扫描过来，判断车还能不能转的下即可。若装得下，那么继续装。装不下则再开一辆车。

温馨提醒：最后出了循环后，再特判一下车里还有没有人。有人则ans+1,否则不加

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a[101], ans;
int main() {
	cin >> n >> m;
	for (register int i = 1; i <= n; ++i) cin >> a[i];//读入数据
	int sum = 0;
	for (register int i = 1; i <= n; ++i) {
		if (sum + a[i] <= m) sum += a[i];//判断车还能否装得下
		else {
			sum = a[i];
			++ans;
		}
	} 
	if (sum != 0) ++ans;//特判，否则你就愉快的WA了
	cout << ans;
}
```

---

## 作者：YosemiteHe (赞：1)

题目大意：

>公交车站有一些人在等车，他们都组成了 $n$ 组，第$i$ 个团体有 $a_i$ 个人。每辆公交车能容纳 $m$ 个人，一次性可以拉好几组人，但一次必须带一整组人，不可以改变组之间的顺序。输出公交车的总数。

直接模拟，一边加上这组的人数，看总数是否大于 $m$，如果是，答案 $+ 1$，累加变量清零。

一开始答案要设为 $1$，因为如果剩下的人数小于 $m$，也要分一辆车。

Code:
```cpp
#include <bits/stdc++.h>
int a, n, m, s, ans = 1;
int main(void) {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a);
        if (m < s + a) {
            ans++;
            s = 0;
        }
        s += a;
    }
    printf("%d\n", ans);
}
```

Tks.

---

## 作者：西宋太祖 (赞：0)

## 题目思路
1. 由于小组次序不能变换，每个组也不能拆分，所以只需要先将第 $i$ 辆车的人数 $s$ 与每辆车能承载的人数 $m$ 进行比较，如果 $s$ 加上第 $j$ 个小组的人数 $a_j$ 小于或等于 $m$，$s$ 则加上 $a_j$；如果 $s$ 加上 $a_j$ 大于 $m$，则总车数加上$1$，并将 $s$ 清零。因为$a_j$还没有被加上，所以将    $j$ 减 1，在下次循环时重新判断这个小组。

1. 如果最后一辆车每有算入（即`s != 0`），则将总车数加上$1$。

## C++代码
```cpp
#include <iostream>
using namespace std;
int main()
{
    int n, m, i, sum = 0, s = 0;
    int a[105];
    cin >> n >> m;
    for(i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for(i = 1; i <= n; i ++)
    {
        if(s + a[i] <= m)
            s += a[i];
        else if(s + a[i] > m)
        {
            sum++;
            s = 0;
            i--;
        }
    }
    if(s != 0)
        sum++;
    cout << sum << endl;
}
```


---

## 作者：Aragron_II (赞：0)

一道很水的题目，就是循环模拟。

#### 题意：
一共有n组人，每一车能拉走m个人。

一次性可以拉好几组人，但一次必须带一整组人，不可以改变组之间的顺序。

求最后用的巴士数量。

#### 分析：

1.循环判断，如果人数 $ <=m $ 则加上这组人。

2.否则计数器+1 ，并将人数赋值为当前组人数。

3.如果当前组人数 $ =m $ 则计数器+1，人数清零。

具体代码：
```c
for(int i=1;i<=n;i++) {
		cin>>a[i];
		if (a[i]+s<=m) s+=a[i];
		else ans++,s=a[i];
		if(a[i]==m) ans++,s=0;
	}
```

最后还要加上特判：

如果 $ s>0 $ 则计数器加1

一定要加不然会 $ WA $

#### 完整代码：

```c
#include <bits/stdc++.h>
using namespace std;
int a[2000],n,m,ans,s;
int main() {
    cin>>n>>m;//输入n组人，车容量m
    for(int i=1;i<=n;i++) {
		cin>>a[i];
		if (a[i]+s<=m) s+=a[i];//上述分析1
		else ans++,s=a[i];//上述分析2
		if(a[i]==m) ans++,s=0;//上述分析3
	}
    if(s) ans++;//特判
    cout<<ans<<endl; //输出
    return 0;
}
```



---

## 作者：Soshine_溯闪 (赞：0)

我 **第六次** 传题解。    
这是一道模拟题。     
# 整体思路
1. 因为组不能拆而且顺序不能变，所以一层循环就可以了。    
2. 如果这组上了不超载：   
那么就上车，将这组人数加上现在车现有人数。    
3. 上了会超载：    
那么就需要新的一辆车了，现需车数加一，将这辆车的现载人量置成这组人数。 
4. 别忘处理最后一辆车：     
因为题目要求的是肯定有组上车的，所以 $now$ 定是非零的，也就是现在至少有一辆车没装满，但是当所有组都上车后，最后一辆车没加在 $ans$ 里面，所以程序后面处理了一下
# 结合着程序，思考一下   
```
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdio>
#include <queue>
#include <map>
#include <iomanip>
using namespace std;
int n,m,a[101]; 		//定义 
int main(){
	cin>>n>>m;		//输入 
	int now=0,ans=0;		//定义 
	for(int i=1;i<=n;i++) cin>>a[i];		//输入 
	for(int i=1;i<=n;i++){		//开始枚举 
		if(now+a[i]<=m) now+=a[i];		//不超载就上车 
		else {		//否则 
			ans++;			//来新车	
			now=a[i];		//现在这辆车有人数重置 
		}
	}
	ans++;		//处理最后一辆 
	cout<<ans<<endl;		//输出 
	return 0;
}
```
求管理员给过！

---

## 作者：cq_loves_Capoo (赞：0)

这题的思路大致如下：    
先输入第i组人的人数。   
接着判断巴士是否能容下这组人的人，如果能，则累加，否则就累计巴士量加一，人数清零。
最后输出（这个好像不用说了吧。）
代码：     
``` 
#include<bits/stdc++.h>//方便的万能头~ 
using namespace std;
int n,m,s,ans=1/*注意初始巴士量为1*/,sum;
int main()
{
	scanf("%d%d",&n,&m);//输入n和m 
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&s);//输入每组人人数 
		if(s+sum>m/*判断是否能容下*/) ans++/*如果不能容下这组人，巴士量+1*/,sum=0/*人数清零*/;
		sum+=s;//累加 
	}
	printf("%d",ans);//输出答案
	return 0; 
}
```
**请勿复制粘贴！**


---

## 作者：CobaltChloride (赞：0)

```
贪心题
不用多说,暴力
#include<bits/stdc++.h>
using namespace std;
int a[101],n,i,j,m,ans,p;
int main(){
    cin>>n>>m;
    for(i=1;i<=n;i++) cin>>a[i];
    i=1;//初始化
    while(i<=n){
        p+=a[i];//装车
        if(p>m){
            p=0;//清零
            ans++;//下一辆来
        }
        else i++;//如果装满了,则把该组人赶下车,i不++
    }
    if(p!=0) ans++;//如果最后还有剩下的人,得再派一辆车
    cout<<ans;
    return 0;
}
```

---

## 作者：damage (赞：0)

# 题意

一共有$n$组人（小于等于巴士容量），每一车能拉走$m$个人。

一次性可以拉好几组人，但一次必须带一整组人，不可以改变组之间的顺序。

求最后用的巴士数量。

---

# 题解

直接膜你贪心，记录等这班车的人数。

对于每组人，如果能带走就带走，带不走就让他们等下一班巴士。

具体详情见代码注释。

---

# 代码

```cpp
#include<stdio.h>
int n,m,a,wait,res; //wait表示当前等着走的人数
int main()
{
	scanf("%d%d",&n,&m);
	while(n--) //输入每组人数
	{
		scanf("%d",&a);
		if(a+wait<=m) wait+=a; //如果巴士能够带走这组人数加上之前等着走的人数，就让这组也加入等的行列
		else //如果无法全部带走
		{
			++res; //多用一辆巴士
			wait=a; //带走之前等的人（wait=0），然后让这组人等（wait=a）
		}
	}
	if(wait) ++res; //注意特判是否还剩下人
	printf("%d\n",res);
	return 0;
}
```

---

## 作者：Nozebry (赞：0)

## $Problems$
一共有 $n$ 组人在排队等公交车，每一辆公交
车能载 $m$个人。 $($ $1\le n,m \le 100$ $)$ 

每一组的 $a_i$ $($ $1\le a_i \le m$ $)$ 个人只会上同一辆车，如果坐不下就等下一辆车，并且严格按照队伍的顺序上车，即如果第 $1$ 组人没上车，则第 $2$ 到第 $n$ 组的人也无法上车。

现在要你求最少需要多少辆车才能把所有人都载走 $?$
## $Answer$
一道简单的模拟题，我们只需要按照队伍的顺序依次向后访问，当前组能够上车就上车，不能够上车就等下一趟，一直做这件事知道 $n$ 组人都上车了。
## $Code$
```pascal
var
    n,m,ans,sum,i:longint;
    a:array[0..1010]of longint;
begin
    readln(n,m);
    for i:=1 to n do read(a[i]);
    ans:=0;sum:=0;
    i:=1;
    while i<=n do
    begin
        sum:=sum+a[i];
        if sum>=m then//当这辆车的没有被浪费，即坐满了，则累加车数
        begin
            if (sum=m) then
            begin
                sum:=0;
                inc(ans);//刚好坐满，统计上车人数的 sum 清 0，车数 ans 加1
            end
            else
            begin
                sum:=0;
                inc(ans);
                dec(i);//如果超出最大载重量，则第 i 组的人不上车
            end;
        end;
        inc(i);
    end;
    if sum<>0 then inc(ans);//如果还有人没上车，则公交车数加1
    writeln(ans);
end.

```

---

