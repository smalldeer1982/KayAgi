# Taxi

## 题目描述

After the lessons $ n $ groups of schoolchildren went outside and decided to visit Polycarpus to celebrate his birthday. We know that the $ i $ -th group consists of $ s_{i} $ friends ( $ 1<=s_{i}<=4 $ ), and they want to go to Polycarpus together. They decided to get there by taxi. Each car can carry at most four passengers. What minimum number of cars will the children need if all members of each group should ride in the same taxi (but one taxi can take more than one group)?

## 说明/提示

In the first test we can sort the children into four cars like this:

- the third group (consisting of four children),
- the fourth group (consisting of three children),
- the fifth group (consisting of three children),
- the first and the second group (consisting of one and two children, correspondingly).

There are other ways to sort the groups into four cars.

## 样例 #1

### 输入

```
5
1 2 4 3 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
8
2 3 4 4 2 1 3 1
```

### 输出

```
5
```

# 题解

## 作者：ZolaWatle (赞：5)

### CF158B 题解

基本思路：**模拟**

1. 出租车最多能坐四人，每组最多四人，而且好姐妹不能分离。

2. 因此，恰好有四个人的那一组必坐同一辆车。

```cpp
ans+=sum[4];
```


3. 同理，可以把两个二人组看成一个四人组。

```cpp
ans+=sum[2]/2;
```


4. 有多余的两人组再发派单身狗。

```cpp
if(sum[2]%2!=0)  //有剩下的一个二人组 
{
	ans++;
	if(sum[1]>=2)  //单身狗数量大于两个，可以凑成四人组
		sum[1]-=2;
	else if(sum[1]>=1)  //单身狗只有一个，分一个，然后让单身狗消失 
		sum[1]--;
}
```


5. 最后把单身狗和三人组分一起。

6. 如果多出来的是单身狗，那么把四只单身狗看作一个四人组，如果多出来的是三人组，那就没办法了。因为好姐妹不能分离，所以有多少组就再安排几辆车。

```cpp
if(sum[1]==sum[3])
	ans+=sum[1];  //刚好凑出来四人组 
else if(sum[1]>sum[3])  //剩下一些单身狗 
{
	ans+=sum[3];
	sum[1]-=sum[3];
	ans+=sum[1]/4;  //四只单身狗抱团取暖 
	if(sum[1]%4!=0)  //还有剩下的
		ans++;
}
else if(sum[1]<sum[3])  //剩下三人组，没有办法 
	ans+=sum[3];
```


分析完毕，接下来是完整代码。

有一个细节问题，其实这题不用开a[i]数组，用局部变量即可。

**CODE（不要copy哦~）:**

```cpp
#include <iostream>
#include <cstdio>
#define re register int
using namespace std;

int n,ans,sum[5]/*这个用来存有i个人的组合有多少个*/;

int main()
{
	std::scanf("%d",&n);
	for(re i=1;i<=n;i++)
	{
		re temp;  //代替数组 
		std::scanf("%d",&temp);
		sum[temp]++;  //组数++ 
	}
	
	ans+=sum[4];
	ans+=sum[2]/2;
	if(sum[2]%2!=0)  //有剩下的一个二人组 
	{
		ans++;
		if(sum[1]>=2)  //单身狗数量大于两个，可以凑成四人组
			sum[1]-=2;
		else if(sum[1]>=1)  //单身狗只有一个，分一个，然后让单身狗消失 
			sum[1]--;
	}
		
		
	if(sum[1]==sum[3])
		ans+=sum[1];  //刚好凑出来四人组 
	else if(sum[1]>sum[3])  //剩下一些单身狗 
	{
		ans+=sum[3];
		sum[1]-=sum[3];
		ans+=sum[1]/4;  //四只单身狗抱团取暖 
		if(sum[1]%4!=0)  //还有剩下的
			ans++;
	}
	else if(sum[1]<sum[3])  //剩下三人组，没有办法 
		ans+=sum[3];
		
	std::printf("%d",ans);  //输出就行了 
	return 0;
}
```

算法不是最优解，仅代表个人意见。有更好方法的欢迎提出。

---

## 作者：FL_sleake (赞：4)

提供一种不需要写 if-else 语句的码量极小的代码。

### 解题思路

考虑尽量塞满每一辆出租车。那么四个人的小组就直接一辆车即可。三个人的小组和一个人的小组组合在一起收益最大，尽量多组合。

最后如果剩下三个人的小组，说明此时没有一个人的小组了，那么只能三个人的小组单独一辆车。

如果剩下一个人的小组，说明此时没有三个人的小组了。

注意到如果只剩下两个人的小组和一个人的小组，几乎可以以任意方式塞满车，所以只需要总人数除以四上取整辆车。

把上述需要的车辆数加起来就是答案。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int cnt[5];
signed main(){
	int n;
	cin>>n;
	for(int i=1,x;i<=n;i++) cin>>x,cnt[x]++;
	int t=min(cnt[3],cnt[1]);
	cnt[4]+=t;
	cnt[3]-=t;
	cnt[1]-=t;
	cout<<cnt[4]+cnt[3]+(cnt[2]*2+cnt[1]*1+4-1)/4<<endl;
	return 0;
}
```

---

## 作者：Katsura_Hinagiku (赞：3)

大概。。。是贪心吧。。

~~贪就完事了~~

考虑让每一辆出租车坐尽可能多的人

四个人的只能一组一辆车

三个人的和一个人的拼车

二个人的和二个人的拼车

接着是2+1+1

和1+1+1+1

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a1,a2,a3,a4,n;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
	{
		int k;
		scanf("%d",&k);
		if(k==1)++a1;
		if(k==2)++a2;
		if(k==3)++a3;
		if(k==4)++a4;//分别统计有1、2、3、4个人的组数 
	}
	int ans=a4;//4个人一组的只能一组坐一辆出租车 
	ans+=a3;
	a1=max(a1-a3,0);//3个人一组的可以与1个人一组的拼车
	ans+=a2/2;
	a2%=2;//2个人一组的2组拼一辆车
	if(a2)
	{
		++ans;
		a1=max(a1-2,0);
	}//如果还有2人一组的没有坐上车，可以和2组一人一组的拼车
	if(a1)
	{
		if(a1%4)ans+=a1/4+1;
		else ans+=a1/4;
	}//最后剩下1人一组的四组拼一辆车，如果还有剩下的，全部塞进一辆车中
	printf("%d\n",ans); 
	return 0;
}
```

---

## 作者：yjiong (赞：2)

### 题意：
将小组各种搭配，每次都尽量凑齐四人。


------------


按照这种思路，我们可以得到几种搭配方案：$4$，$1-3$，$2-2$，$1-1-2$，$1-1-1-1$。

既然这样，那我们就可以用一个数组来维护每组组员个数分别为 $1$ 到 $4$ 的组的数量，先将 $4$，$1-3$，以及 $2-2$ 这 $3$ 种可以凑整的凑了，余下的若是 $3$，则 $3$ 和 $2$ 组（余 $3$ 则不可能余 $1$，因此不可能出现 $1-1-2$ 的情况，所以 $2$ 只能单独成组），若是 $1$，则先将余下的 $2$ 和 $1$ 搭配成一组，最后若 $1$ 还有剩余，则考虑 $1-1-1-1$ 的情况。

代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
int sum[5];
int main(){
	int a, n, ans = 0;
	cin >> n;
	for(int i = 1; i <= n; ++ i){
		cin >> a;
		sum[a] ++;
	}
	ans += sum[4];//4人一组的只能单独开一车 
	if(sum[1] <= sum[3]){//余3的情况 
		ans = ans + sum[3];//余下的3不管怎样都要单开一车 
		ans = ans + ceil(1.0 * sum[2] / 2); 
	}
	else{//余1的情况 
		ans += sum[3]; 
		sum[1] -= sum[3];//剩下的1 
		ans += sum[2] / 2;
		sum[2] %= 2;
		if(sum[2]) ans ++ , sum[1] -= 2;//若2还有剩余，则和1搭配 
		if(sum[1] > 0) ans += ceil(1.0 * sum[1] / 4);//1-1-1-1的情况 
	}
	cout << ans;
    return 0;
}
```


---

## 作者：Register (赞：2)

## if水题
这道题题面似乎不是很完整，没有说出租车作为有几个，虽然出租车车位有$4$个是常识，但还是顺带说一句吧~~实际是因为我做题的时候被这东西卡住了~~

我们来分析一下这道题：

	利用凑整的思想，尽量将每车人数凑满
    首先4人一队，没话可说，肯定车数会增加四人帮的个数
    接着1人一队，可以和2人，3人自由组合。他是一个主动方，2人除了和1人还可以和自己，也算是主动方，而3人只能和1人组合，是被动，为了省钱，1要尽量和3组合
    2人首先自己匹配自己（为什么我想到了KMP），如果有单的，就看有没有余下的1，据情况而论
奉上代码：

```cpp
#include <iostream>
using namespace std;
int n,team[5]/*相当于一个桶*/,sum,a;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) {cin>>a;team[a]++;}
    sum+=team[4];//将4加进去
    sum+=team[2]/2;
    if(team[2]%2==0)//如果2能凑整
    {
        if(team[1]>team[3]) sum+=team[3]+((team[1]-team[3])%4==0?(team[1]-team[3])/4:(team[1]-team[3])/4+1);//如果1多
        else sum+=team[3];//3多
    }
    else
    {
        if(team[1]>team[3]) sum+=team[3]+((team[1]-team[3]+2)%4==0?(team[1]-team[3]+2)/4:(team[1]-team[3]+2)/4+1);//如果1多
        else sum+=team[3]+1;3多
    }
    cout<<sum<<endl;//输出
    return 0;
}
```

---

## 作者：HNYLMS_MuQiuFeng (赞：2)

这道题其实不难的，我也不知道为什么会是黄题

# 主要思想：
#### 1尽量多的和3配，2尽量多的和2配

废话不多说，直接上代码
```cpp
#include<iostream>//不用万能头文件从我做起
#include<cstdio>
#include<algorithm>
using namespace std;
int n,sum,num2,num3,num4,num1,a;//num1 2 3 4计数器
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a;
		if(a==1)num1++;//统计各个数字出现次数
		if(a==2)num2++;
		if(a==3)num3++;
		if(a==4)num4++;
	 } 
	 if(num1<=num3)//因为3没法和1以上的配所以当num1<=num3的时候1，3一共
     //需要num3辆巴士
	 {
	 	sum+=num3;
	 	sum+=num4;//4个人直接占一辆巴士
	 	if(num2%2==0)sum+=num2/2;//判断2奇偶
        //因为1都配3去了所以没有1来配2
	 	else sum+=num2/2+1;
	 }
	 if(num1>num3)//num1>num3时先把3解决，剩下的1先配2，再和自己配
	 {
	 	sum+=num3;
	 	num1-=num3;
	 	sum+=num4;
	 	if(num2%2==0)sum+=num2/2;
	 	else 
	 	{
	 		sum+=num2/2+1;num1-=2;if(num1<0)num1=0;
            //多一个2的时候要配过去两个1（考虑num1<0的情况）
		 }
		 if(num1%4==0)sum+=num1/4;//1和自己配
		 else sum+=num1/4+1;
	 }
	 cout<<sum;//愉快的输出，AC啦！
	return 0;
}
```
# 本题解仅供参考，杜绝抄袭，从我做起！！！

---

