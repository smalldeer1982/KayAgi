# 题目信息

# Gourmet Cat

## 题目描述

Polycarp has a cat and his cat is a real gourmet! Dependent on a day of the week he eats certain type of food:

- on Mondays, Thursdays and Sundays he eats fish food;
- on Tuesdays and Saturdays he eats rabbit stew;
- on other days of week he eats chicken stake.

Polycarp plans to go on a trip and already packed his backpack. His backpack contains:

- $ a $ daily rations of fish food;
- $ b $ daily rations of rabbit stew;
- $ c $ daily rations of chicken stakes.

Polycarp has to choose such day of the week to start his trip that his cat can eat without additional food purchases as long as possible. Print the maximum number of days the cat can eat in a trip without additional food purchases, if Polycarp chooses the day of the week to start his trip optimally.

## 说明/提示

In the first example the best day for start of the trip is Sunday. In this case, during Sunday and Monday the cat will eat fish food, during Tuesday — rabbit stew and during Wednesday — chicken stake. So, after four days of the trip all food will be eaten.

In the second example Polycarp can start his trip in any day of the week. In any case there are food supplies only for one week in Polycarps backpack.

In the third example Polycarp can start his trip in any day, excluding Wednesday, Saturday and Sunday. In this case, the cat will eat three different dishes in three days. Nevertheless that after three days of a trip there will be $ 99 $ portions of rabbit stew in a backpack, can cannot eat anything in fourth day of a trip.

## 样例 #1

### 输入

```
2 1 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 2 2
```

### 输出

```
7
```

## 样例 #3

### 输入

```
1 100 1
```

### 输出

```
3
```

## 样例 #4

### 输入

```
30 20 10
```

### 输出

```
39
```

# AI分析结果

### 题目重写
Polycarp有一只猫，这只猫的饮食规律如下：
- 在每周的周一、周四、周日，猫咪会吃一条鱼；
- 在每周的周二、周六，猫咪会吃一份兔肉；
- 剩下的时间猫咪会吃一份鸡肉。

Polycarp计划去旅行，并已经准备好了背包。他的背包里有：
- $a$ 条鱼；
- $b$ 份兔肉；
- $c$ 份鸡肉。

Polycarp需要选择一周中的某一天开始旅行，使得他的猫在不需要额外购买食物的情况下能够吃得尽可能久。请输出猫在最优选择下能够吃的最多天数。

### 算法分类
模拟、枚举

### 题解分析与结论
1. **周期优化**：所有题解都提到了利用周期优化，即先计算猫可以吃多少个整周（$\min(a/3, b/2, c/2)$），然后减去整周的消耗，再枚举从一周中的哪一天开始，模拟剩余的食物的消耗情况。
2. **枚举与模拟**：枚举从一周中的哪一天开始，模拟食物的消耗过程，直到某种食物不足为止。这种方法虽然简单，但在优化后能够有效减少计算量。
3. **代码实现**：大部分题解的代码结构相似，先计算整周数，然后枚举起始日，模拟食物的消耗，最后输出结果。

### 评分较高的题解
#### 题解1：yeshubo_qwq (4星)
- **关键亮点**：代码简洁，逻辑清晰，直接利用周期优化和枚举模拟，代码可读性高。
- **核心代码**：
```cpp
int a,b,c,d,A,B,C,i,j,ma;
int main(){
	cin>>a>>b>>c;
	d=min(a/3,min(b/2,c/2));//求出周期数 
	a-=d*3;b-=d*2;c-=d*2; 
	for(i=0;i<=6;i++){//枚举星期几出发，0表示星期日 
		A=a;B=b;C=c;j=i;
		while(1){
			if(j%7==1||j%7==4||j%7==0)A--; 
			else if(j%7==2||j%7==6)B--;
			else C--; 
			if(A<0||B<0||C<0)break;//不够吃退出循环 
			j++;//又吃了一天 
		}
		ma=max(ma,j-i);
	}
	cout<<ma+d*7;//最大值+周期*7即为所求答案 
	return 0;
}
```

#### 题解2：一扶苏一 (4星)
- **关键亮点**：详细解释了周期优化的思路，代码结构清晰，注释详细，适合初学者理解。
- **核心代码**：
```cpp
ll a, b, c, ans;
int main() {
  qr(a); qr(b); qr(c);
  ans = std::min(a / 3, std::min(b / 2, c / 2));
  a -= 3 * ans; b -= ans << 1; c -= ans << 1;
  ans *= 7;
  ll tt = 0;
  for (int i = 1; i <= 7; ++i) {
    ll ta = a, tb = b, tc = c;
    ll ts = 0;
    int day = i;
    while (true) {
      if ((day == 1) || (day == 4) || (day == 7)) {
        if (ta-- == 0) break;
      } else if ((day == 2) || (day == 6)) {
        if (tb-- == 0) break;
      } else if (tc-- == 0) break;
      ++day; ++ts;
      if (day == 8) day = 1;
    }
    tt = std::max(tt, ts);
  }
  qw(ans + tt, '\n', true);
  return 0;
}
```

### 最优关键思路
1. **周期优化**：先计算猫可以吃多少个整周，减少模拟的数据量。
2. **枚举与模拟**：枚举从一周中的哪一天开始，模拟食物的消耗过程，直到某种食物不足为止。

### 可拓展之处
- **类似问题**：可以考虑其他周期性消耗资源的问题，如能源消耗、物资分配等。
- **优化思路**：在枚举过程中，可以进一步优化模拟的终止条件，减少不必要的计算。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)

---
处理用时：34.37秒