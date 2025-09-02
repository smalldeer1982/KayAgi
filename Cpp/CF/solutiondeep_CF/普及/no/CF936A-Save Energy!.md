# 题目信息

# Save Energy!

## 题目描述

Julia is going to cook a chicken in the kitchen of her dormitory. To save energy, the stove in the kitchen automatically turns off after $ k $ minutes after turning on.

During cooking, Julia goes to the kitchen every $ d $ minutes and turns on the stove if it is turned off. While the cooker is turned off, it stays warm. The stove switches on and off instantly.

It is known that the chicken needs $ t $ minutes to be cooked on the stove, if it is turned on, and $ 2t $ minutes, if it is turned off. You need to find out, how much time will Julia have to cook the chicken, if it is considered that the chicken is cooked evenly, with constant speed when the stove is turned on and at a constant speed when it is turned off.

## 说明/提示

In the first example, the chicken will be cooked for 3 minutes on the turned on stove, after this it will be cooked for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF936A/946fbd87d05fe2e24b8af4d0aa7735f7b1052cc7.png). Then the chicken will be cooked for one minute on a turned off stove, it will be cooked for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF936A/a9bdc1b9aee6e89dbd96641ebe23053a20526f44.png). Thus, after four minutes the chicken will be cooked for ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF936A/6991f0a9cff42170b98fc979c8ddd5223ae7cf0e.png). Before the fifth minute Julia will turn on the stove and after $ 2.5 $ minutes the chicken will be ready ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF936A/b3b22ef8237f8837aeb119d85eaee973ea63486d.png).

In the second example, when the stove is turned off, Julia will immediately turn it on, so the stove will always be turned on and the chicken will be cooked in 20 minutes.

## 样例 #1

### 输入

```
3 2 6
```

### 输出

```
6.5
```

## 样例 #2

### 输入

```
4 2 20
```

### 输出

```
20.0
```

# AI分析结果

### 题目内容重写

#### 题目描述

Julia 准备在她的宿舍厨房里煮一只鸡。为了节省能源，厨房的炉子在开启后会自动在 $k$ 分钟后关闭。

在烹饪过程中，Julia 每隔 $d$ 分钟会去厨房一次，如果炉子是关闭的，她会立即打开它。当炉子关闭时，它会保持温暖状态。炉子的开关是瞬间完成的。

已知，如果炉子是开启的，鸡需要 $t$ 分钟煮熟；如果炉子是关闭的，鸡需要 $2t$ 分钟煮熟。你需要计算 Julia 煮熟这只鸡所需的总时间，假设鸡在炉子开启和关闭时的烹饪速度是恒定的。

#### 说明/提示

在第一个例子中，鸡会在开启的炉子上煮 3 分钟，之后会在关闭的炉子上煮 1 分钟。因此，4 分钟后，鸡已经煮熟了。在第五分钟之前，Julia 会再次打开炉子，并在 $2.5$ 分钟后鸡完全煮熟。

在第二个例子中，当炉子关闭时，Julia 会立即打开它，因此炉子始终是开启的，鸡将在 20 分钟内煮熟。

#### 样例 #1

##### 输入

```
3 2 6
```

##### 输出

```
6.5
```

#### 样例 #2

##### 输入

```
4 2 20
```

##### 输出

```
20.0
```

### 算法分类

**数学**

### 题解分析与结论

所有题解的核心思路都是将问题转化为周期问题，通过计算每个周期内鸡的烹饪进度，最终得出总时间。以下是各题解的要点对比：

1. **hjsxhst2022** 和 **Provider** 的题解思路相似，都是通过计算 $d$ 的几倍达到 $k$ 来定义一个周期，然后计算周期内的烹饪进度，最后处理剩余时间。代码实现上，两者都使用了 `setprecision` 来控制输出精度。
   
2. **hao_zi6366** 的题解思路也类似，但更注重周期的定义和剩余时间的处理。代码中使用了 `std::ceil` 来计算周期长度。

3. **封禁用户** 和 **JustinXiaoJunyang** 的题解思路与前两者一致，代码实现上也较为相似，都使用了 `setprecision` 来控制输出精度。

4. **lizhixun** 的题解思路与前几者一致，代码实现上使用了 `#define int long long` 来避免整数溢出问题。

### 最优关键思路

1. **周期计算**：通过计算 $d$ 的几倍达到 $k$ 来定义一个周期，这是所有题解的核心思路。
2. **剩余时间处理**：在计算完完整周期后，需要单独处理剩余时间的烹饪进度，这是所有题解的难点。
3. **精度控制**：使用 `setprecision` 来控制输出精度，确保结果的准确性。

### 推荐题目

1. **P1008 三连击**（考察周期与数学计算）
2. **P1012 拼数**（考察数学与字符串处理）
3. **P1028 数的计算**（考察递推与数学思维）

### 个人心得摘录

- **hjsxhst2022**：提到“小学数学！小学数学！！小学数学！！！”强调本题的数学性质。
- **lizhixun**：提到“不开 `long long` 会见祖宗哦”，强调了数据类型选择的重要性。

### 精选题解

#### 题解1：hjsxhst2022 (4星)

**关键亮点**：思路清晰，代码简洁，使用了 `setprecision` 控制输出精度。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,m;
	double k,d,t,x,qwq,qaq;
	cin>>k>>d>>t;
	n=(k-1)/d+1;
	x=n*d;
	m=t*2/(x+k);
	qwq=t*2-(x+k)*m;
	qaq+=x*m;
	if(qwq<=k*2-1)
		qaq+=qwq/2;
	else
		qaq+=k,qaq+=qwq-k*2;
	cout<<setprecision(10)<<qaq;
}
```

#### 题解2：Provider (4星)

**关键亮点**：思路清晰，代码简洁，使用了 `setprecision` 控制输出精度。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
double k,d,t,ans=0,r,rlen,change,rou;
int main()
{
    cin>>k>>d>>t; 
	r=(long long)((k-1)/d)+1;
	rlen=r*d;
	change=(long long)(2*t/(rlen+k));
	rou=2*t-(rlen+k)*change;
	ans+=change*rlen;
	if(rou<2*k) 
	ans+=rou/2;
	else ans+=k,ans+=rou-2*k;
	cout<<fixed<<setprecision(1)<<ans;
	return 0;
}
```

#### 题解3：hao_zi6366 (4星)

**关键亮点**：思路清晰，代码简洁，使用了 `std::ceil` 计算周期长度。

**核心代码**：
```cpp
#include<bits/stdc++.h>
typedef long long ll;

int main(){
	std::ios::sync_with_stdio(0);
	std::cout.tie(0);
	std::cin.tie(0);
	
	double d,t,k;
	std::cin>>k>>d>>t;
	double yici=(std::ceil(k/d)*d-k)/2+k;
	ll cishu=t/yici;
	double yu=(t-yici*cishu),ans;
	if(yu<=k) ans=yu+(std::ceil(k/d)*d)*cishu;
	else ans=(std::ceil(k/d)*d)*cishu+k+(yu-k)*2;
	std::cout<<std::fixed<<std::setprecision(9)<<ans;
	return 0;
}
```

---
处理用时：43.30秒