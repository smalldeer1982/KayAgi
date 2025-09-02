# 题目信息

# [NWRRC 2014] Alarm Clock

## 题目描述



Alice likes her digital alarm clock. She sets them up every evening. Last night Alice had a dream about her clock. Unfortunately, the only thing she is able to remember is the number of highlighted segments of the clock. Alice wonders what time was set on the clock in her dream.

Alice's clock have four digits: two for hours and two for minutes. For example, the clock below shows $9:30$ (note the leading zero).

![](https://cdn.luogu.com.cn/upload/image_hosting/6dl4fhwk.png)

The clock uses following digit representation.

![](https://cdn.luogu.com.cn/upload/image_hosting/igdzsez5.png)



## 说明/提示

Time limit: 2 s, Memory limit: 256 MB. 

spj provider: @[rzh123](user/237530)

## 样例 #1

### 输入

```
23
```

### 输出

```
09:30
```

## 样例 #2

### 输入

```
28
```

### 输出

```
Impossible
```

## 样例 #3

### 输入

```
2
```

### 输出

```
Impossible
```

# AI分析结果

### 算法分类
枚举

### 综合分析与结论
题目要求根据给定的火柴棒数量，找出一个合法的时间表示。所有题解的核心思路都是通过枚举所有可能的时间（00:00到23:59），并计算每个时间所需的火柴棒数量，判断是否与输入匹配。虽然题目本身较为简单，但题解中展示了不同的实现方式和优化技巧。

### 所选高星题解

#### 1. 作者：幻想繁星 (4星)
**关键亮点**：
- 使用预处理数组存储每个数字所需的火柴棒数量，简化了计算过程。
- 使用`printf`自动补零，避免了手动处理前导零的麻烦。
- 代码简洁明了，逻辑清晰。

**核心代码**：
```cpp
int n[10]={6,2,5,5,4,5,6,3,7,6},a,s;
for(int i=0;i<=23;i++) for(int j=0;j<60;j++) {
    s=0;
    s+=n[i%10]; s+=n[i/10]; s+=n[j%10]; s+=n[j/10];
    if(s==a) {
        printf("%02d:%02d",i,j);
        return 0;
    }
}
cout<<"Impossible";
```

#### 2. 作者：iterator_it (4星)
**关键亮点**：
- 自定义`print`函数处理前导零，增强了代码的可读性。
- 使用常量数组存储火柴棒数量，减少了重复计算。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
const int num[]={6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
void print(int x) {
    if(x<10) cout<<0;
    cout<<x;
}
for(int i=0;i<24;i++) for(int j=0;j<60;j++) {
    int a=i/10,b=i%10,c=j/10,d=j%10;
    if((num[a]+num[b]+num[c]+num[d])==n) {
        print(i); cout<<":"; print(j);
        return 0;
    }
}
cout<<"Impossible";
```

#### 3. 作者：Supor__Shoep (4星)
**关键亮点**：
- 使用自定义`print`函数处理前导零和冒号，简化了输出逻辑。
- 代码结构清晰，逻辑简单，易于理解。
- 通过双重循环枚举所有可能的时间，效率较高。

**核心代码**：
```cpp
void print(int n,int m) {
    if(n<10) cout<<"0";
    cout<<n<<":";
    if(m<10) cout<<"0";
    cout<<m;
}
for(int i=0;i<24;i++) for(int j=0;j<60;j++) {
    if(hc[i/10]+hc[i%10]+hc[j/10]+hc[j%10]==n) {
        print(i,j);
        return 0;
    }
}
cout<<"Impossible";
```

### 最优关键思路
1. **预处理数组**：使用数组存储每个数字所需的火柴棒数量，简化了计算过程。
2. **自动补零**：使用`printf`或自定义函数处理前导零，避免了手动处理的麻烦。
3. **双重循环枚举**：通过双重循环枚举所有可能的时间，确保不漏解。

### 可拓展之处
类似的问题可以扩展到其他形式的数字表示，如日期、电话号码等，要求根据给定的条件（如火柴棒数量、特定数字组合等）找出符合条件的表示。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)
3. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)

### 个人心得摘录
- **幻想繁星**：通过预处理数组和`printf`自动补零，简化了代码逻辑，提高了可读性。
- **iterator_it**：自定义`print`函数处理前导零，增强了代码的可读性和可维护性。
- **Supor__Shoep**：通过双重循环枚举所有可能的时间，确保不漏解，代码结构清晰，逻辑简单。

---
处理用时：33.48秒