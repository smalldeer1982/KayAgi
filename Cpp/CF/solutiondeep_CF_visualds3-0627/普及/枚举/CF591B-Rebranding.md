# 题目信息

# Rebranding

## 题目描述

The name of one small but proud corporation consists of $ n $ lowercase English letters. The Corporation has decided to try rebranding — an active marketing strategy, that includes a set of measures to change either the brand (both for the company and the goods it produces) or its components: the name, the logo, the slogan. They decided to start with the name.

For this purpose the corporation has consecutively hired $ m $ designers. Once a company hires the $ i $ -th designer, he immediately contributes to the creation of a new corporation name as follows: he takes the newest version of the name and replaces all the letters $ x_{i} $ by $ y_{i} $ , and all the letters $ y_{i} $ by $ x_{i} $ . This results in the new version. It is possible that some of these letters do no occur in the string. It may also happen that $ x_{i} $ coincides with $ y_{i} $ . The version of the name received after the work of the last designer becomes the new name of the corporation.

Manager Arkady has recently got a job in this company, but is already soaked in the spirit of teamwork and is very worried about the success of the rebranding. Naturally, he can't wait to find out what is the new name the Corporation will receive.

Satisfy Arkady's curiosity and tell him the final version of the name.

## 说明/提示

In the second sample the name of the corporation consecutively changes as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/b0c9599f7e4282de011e545b3b2138ce054cf709.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/b503b89dff83c09912a9706615e9f382f03f5909.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/e277cc6136141b35244d23f5857e2b4088822639.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/cfe2461ca78ee24244102008b38c52289020e201.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/c06bdcdcec7417c4f543399c6c3d126f67ecf0a6.png)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF591B/e46b37134536ad3b6c864840e66c2932fc25c838.png)

## 样例 #1

### 输入

```
6 1
police
p m
```

### 输出

```
molice
```

## 样例 #2

### 输入

```
11 6
abacabadaba
a b
b c
a d
e g
f a
b b
```

### 输出

```
cdcbcdcfcdc
```

# AI分析结果



## 算法分类  
**字符映射维护**

---

## 综合分析与结论  
### 核心思路  
通过维护字符映射表，将多次交换操作转化为最终字符对应关系，时间复杂度从 O(nm) 优化到 O(m+n)。所有题解的核心思想均围绕以下两点：  
1. **建立映射表**：记录每个字符最终会被替换成什么字符  
2. **逆向推导**：通过维护交换操作的历史记录，直接得出最终映射关系  

### 解决难点  
- **暴力不可行**：直接模拟每次交换会导致 O(nm) 超时  
- **映射维护技巧**：交换操作需要正确传递到后续步骤（如 `a→b→c` 等效于 `a→c`）  
- **高效更新**：通过数组索引直接交换，避免遍历所有字符  

### 可视化设计  
- **动画方案**：  
  1. 初始化时展示26个字母各自独立的映射块（如像素方块）  
  2. 每次操作高亮两个待交换字母（如红色边框），交换其映射块位置  
  3. 最终映射表生成后，用流动箭头展示原始字符串的每个字符如何按映射表转换  
- **复古效果**：  
  - 使用 8-bit 音效（交换时播放 "beep" 音，完成时播放马里奥过关音效）  
  - 映射块采用 FC 红白机风格的16色像素块，右侧显示当前映射表  
  - 背景音乐采用8位芯片音乐循环播放  

---

## 题解清单 (≥4星)  

### 作者：qian_shang (⭐⭐⭐⭐⭐)  
**亮点**：  
- 双数组映射（正向+逆向），代码极简  
- 时间复杂度 O(m+26+n)，空间最优  
**核心代码**：  
```cpp
swap(f1[a-'a'], f1[b-'a']);  // 交换映射表
for(int i=0;i<26;i++) f2[f1[i]-'a']=i+'a';  // 生成逆向映射
```

### 作者：nightwatch.ryan (⭐⭐⭐⭐)  
**亮点**：  
- 使用 `tmp` 和 `ans` 双数组清晰分离正向/逆向操作  
- 直接操作 ASCII 码提升效率  
**核心代码**：  
```cpp
swap(tmp[r1-97], tmp[r2-97]);  // 交换映射关系
ans[tmp[i]-97] = i+97;        // 生成最终结果
```

### 作者：fish_gugu (⭐⭐⭐⭐)  
**亮点**：  
- 强调 `char[]` 相比 `string` 的优势  
- 详细注释初始化与转换步骤  
**核心代码**：  
```cpp
swap(r[a-97], r[b-97]);       // 交换字母序号
a2[r[i]-97] = i+97;           // 转换为最终字母
```

---

## 最优思路提炼  
**核心代码实现**：  
```cpp
// 初始化映射表（每个字符指向自己）
char mapping[26];
for(int i=0; i<26; i++) mapping[i] = 'a' + i;

// 处理每次交换操作
while(m--) {
    swap(mapping[a-'a'], mapping[b-'a']); // 关键交换步骤
}

// 生成结果字符串
for(char c : original_str) {
    result += mapping[c-'a'];
}
```

---

## 类似题目推荐  
1. **P5587 打字练习** - 字符替换与统计  
2. **P1150 Peter的烟** - 循环替换的数学优化  
3. **CF978B File Name** - 字符串批量操作优化  

---

## 个人心得摘录  
> "**直接模拟必死，要抓住操作的可叠加性**" —— qian_shang  
> "**数组下标比map快至少3倍，尤其是26字母场景**" —— fish_gugu  

---

## 复古像素化演示代码（关键片段）  
```javascript
// 初始化 Canvas 像素网格
const grid = new PixelGrid(26, 1, {x:16, y:16}); 

// 映射块更新动画
function playSwapAnim(a, b) {
    grid.cells[a].moveTo(b*16, 0, {duration: 200});
    grid.cells[b].moveTo(a*16, 0, {duration: 200});
    playSound('swap'); // 触发8-bit音效
}

// 自动演示模式
autoPlay(() => {
    for(let op of operations) {
        playSwapAnim(op.a, op.b);
        await delay(500);
    }
    showResultString(); // 最终结果流动展示
});
```

---
处理用时：71.52秒