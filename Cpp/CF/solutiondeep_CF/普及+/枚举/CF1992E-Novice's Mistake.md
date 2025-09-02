# 题目信息

# Novice's Mistake

## 题目描述

One of the first programming problems by K1o0n looked like this: "Noobish\_Monk has $ n $ $ (1 \le n \le 100) $ friends. Each of them gave him $ a $ $ (1 \le a \le 10000) $ apples for his birthday. Delighted with such a gift, Noobish\_Monk returned $ b $ $ (1 \le b \le \min(10000, a \cdot n)) $ apples to his friends. How many apples are left with Noobish\_Monk?"

K1o0n wrote a solution, but accidentally considered the value of $ n $ as a string, so the value of $ n \cdot a - b $ was calculated differently. Specifically:

- when multiplying the string $ n $ by the integer $ a $ , he will get the string $ s=\underbrace{n + n + \dots + n + n}_{a\ \text{times}} $
- when subtracting the integer $ b $ from the string $ s $ , the last $ b $ characters will be removed from it. If $ b $ is greater than or equal to the length of the string $ s $ , it will become empty.

Learning about this, ErnKor became interested in how many pairs $ (a, b) $ exist for a given $ n $ , satisfying the constraints of the problem, on which K1o0n's solution gives the correct answer.

"The solution gives the correct answer" means that it outputs a non-empty string, and this string, when converted to an integer, equals the correct answer, i.e., the value of $ n \cdot a - b $ .

## 说明/提示

In the first example, $ a = 20 $ , $ b = 18 $ are suitable, as " $ \text{2} $ " $ \cdot 20 - 18 = $ " $ \text{22222222222222222222} $ " $ - 18 = 22 = 2 \cdot 20 - 18 $

## 样例 #1

### 输入

```
3
2
3
10```

### 输出

```
3
20 18 
219 216 
2218 2214 
1
165 162 
1
1262 2519```

# AI分析结果

### 题目内容
# 新手的错误

## 题目描述
K1o0n最初遇到的编程问题之一如下：“菜鸟和尚有$n$（$1 \leq n \leq 100$）个朋友。他们每个人在他生日时都给了他$a$（$1 \leq a \leq 10000$）个苹果。菜鸟和尚对这份礼物欣喜若狂，于是他给朋友们回赠了$b$（$1 \leq b \leq \min(10000, a \cdot n)$）个苹果。菜鸟和尚还剩下多少个苹果？”

K1o0n写了一个解决方案，但不小心将$n$的值当作字符串处理，所以$n \cdot a - b$的计算方式有所不同。具体如下：
- 当将字符串$n$与整数$a$相乘时，他会得到字符串$s=\underbrace{n + n + \dots + n + n}_{a\ \text{次}}$
- 当从字符串$s$中减去整数$b$时，会从字符串中删除最后$b$个字符。如果$b$大于或等于字符串$s$的长度，字符串将变为空。

得知此事后，ErnKor对对于给定的$n$，在满足问题约束的情况下，有多少对$(a, b)$使得K1o0n的解决方案能给出正确答案产生了兴趣。

“解决方案给出正确答案”意味着它输出一个非空字符串，并且这个字符串转换为整数后等于正确答案，即$n \cdot a - b$的值。

## 说明/提示
在第一个示例中，$a = 20$，$b = 18$是合适的，因为 “$ \text{2} $” $ \cdot 20 - 18 = $ “$ \text{22222222222222222222} $” $ - 18 = 22 = 2 \cdot 20 - 18$

## 样例 #1
### 输入
```
3
2
3
10
```
### 输出
```
3
20 18 
219 216 
2218 2214 
1
165 162 
1
1262 2519
```

### 综合分析与结论
这些题解主要围绕缩小枚举范围以优化暴力解法展开。多数题解利用$n \cdot a - b$结果的位数限制来缩小$b$的枚举范围，将时间复杂度从$O(ab)$优化到$O(a)$。部分题解通过数学推导，联立方程求解，减少枚举量；有的则从可能的结果值入手，枚举可能的结果来确定$a$和$b$。

### 所选的题解
- **作者：panxz2009 (赞：8)  星级：5星**
    - **关键亮点**：思路清晰，通过幽默解方程，联立两个关于$b$的等式，得到关于$a$、$x$及其位数的方程，利用$x$和其位数范围小的特点，枚举位数解出$x$和$b$，时间复杂度为$\mathcal O(a)$。
    - **重点代码核心思想**：先通过`divide`函数计算$n$的位数，`init`函数预处理出不同长度下$x$可能的值，在`Main`函数中枚举$a$和$x$的长度，根据条件判断并记录符合的$(a, b)$。
    - **核心代码**：
```cpp
int divide(int n){
    int sum = 0;
    while(n){
        sum++;
        n /= 10;
    }
    return sum;
}
void init(){
    string s = to_string(n);
    int now = 0;
    for(int lenx = 1; lenx <= 6; lenx++){
        x[lenx] = x[lenx - 1] * 10 + (s[now] - '0');
        now = (now + 1) % lenn;
    }
}
void Main(){
    scanf("%d", &n);
    lenn = divide(n);
    ans.clear();
    init();
    for(int a = 1; a <= 10000; a++){
        for(int lenx = 1; lenx <= 6; lenx++){
            int b = lenn * a - lenx;
            if(b > 0 && b < min(10000, a * n) && b == n * a - x[lenx]){
                ans.push_back({a, b});
            }
        }
    }
    printf("%d\n", ans.size());
    for(auto tmp : ans){
        printf("%d %d\n", tmp.first, tmp.second);
    }
}
```
 - **作者：lzh9 (赞：6)  星级：4星**
    - **关键亮点**：通过设$m=a\times n - b$及其位数$k_1,k_2$，联立方程得到关于$a$的一元一次方程，通过枚举$m$求解$a$和$b$，并对特殊情况$n = 1$进行特判。
    - **重点代码核心思想**：定义函数将数字转换为字符串及反向转换，在`sol`函数中，对$n = 1$特判输出，否则枚举$m$的可能值，根据方程条件判断并记录符合的$(a, b)$。
    - **核心代码**：
```cpp
void sol()
{
    cur = 0;
    cin>>n;
    if(n==1)
    {
        cout<<9999<<"\n";
        for(long long i=1;i<10000;i++)
        {
            cout<<i+1<<' '<<i<<"\n";
        }
        return;
    }
    string sn=zh(n);
    long long k1=sn.size();
    sn=sn+sn+sn+sn+sn+sn+sn;
    sn=' '+sn;
    for(long long i=1;i<=7;i++)
    {
        long long k2=i;
        string sw=sn.substr(1,i);
        long long w=zh2(sw);
        if((n-k1)==0) continue;
        if((w-k2)%(n-k1)!=0) continue;
        if((w-k2)/(n-k1)>=1&&(w-k2)/(n-k1)<=10000&&(w-k2)/(n-k1)*n-w>=1&&(w-k2)/(n-k1)*n-w<=10000) ansa[++cur]=(w-k2)/(n-k1),ansb[cur]=(w-k2)/(n-k1)*n-w;
    }
    cout<<cur<<"\n";
    for(long long i=1;i<=cur;i++) cout<<ansa[i]<<' '<<ansb[i]<<"\n";
}
```
 - **作者：Yoyo_01 (赞：5)  星级：4星**
    - **关键亮点**：从暴力做法的瓶颈出发，利用$n \cdot a - b$结果最多6位这一特性，得出$b$的优化取值范围$len(n) * a - 6 \leq b < len(n) \times a$，将复杂度降为$\Theta(a)$。
    - **重点代码核心思想**：通过`sizes`函数计算$n$的位数，在`main`函数中枚举$a$，在优化后的$b$范围内枚举$b$，判断是否满足条件并记录结果。
    - **核心代码**：
```cpp
int sizes(int x){
    int res = 0;
    while(x!= 0)
        res++,x /= 10;
    return res;
}

int main(){
    scanf("%d",&t);
    for(int T = 1;T <= t;T++){
        scanf("%d",&n);
        int cnt = 0,len = sizes(n);
        string now = "",nt = to_string(n);
        for(int a = 1;a <= 10000;a++){
            now = now + nt; 
            for(int b = max(len * a - 6,1);b < len * a;b++){
                string q = now.substr(0,len * a - b);
                if(to_string(a * n - b) == q)
                    ans[++cnt] = Ans{a,b};
            }
        }
        printf("%d\n",cnt);
        for(int i = 1;i <= cnt;i++)
            printf("%d %d\n",ans[i].a,ans[i].b);
    }
    return 0;
}
```

### 最优关键思路或技巧
利用$n \cdot a - b$结果的位数限制来缩小枚举范围是核心技巧。无论是通过数学推导联立方程，还是直接得出$b$的取值范围，都基于对这一限制条件的挖掘，从而有效优化暴力枚举的时间复杂度。

### 同类型题或类似算法套路拓展
此类题目通常涉及对特殊计算规则下满足特定条件的参数对的求解。常见套路是分析数据范围，找出关键限制条件，通过数学推导或逻辑分析缩小枚举空间，优化暴力解法。例如在一些字符串与数字混合运算且需满足特定等式的题目中，可类似地利用结果的范围、位数等特性来优化求解过程。

### 洛谷相似题目推荐
 - [P1111 修复公路](https://www.luogu.com.cn/problem/P1111)：涉及对边权和时间的处理，可通过类似分析数据范围和条件限制来优化算法。
 - [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：通过对问题的分析，利用排序等手段优化求解满足特定条件（总等待时间最短）的方案，与本题优化思路有相通之处。
 - [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：需分析操作规则和数据范围，采用合适的数据结构（如优先队列）和算法策略来优化求解过程，与本题寻找最优解的思路类似。 

---
处理用时：46.40秒