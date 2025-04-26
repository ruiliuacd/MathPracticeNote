# MathPracticeNote
After working for many years, I decided to reorganize and learn some key mathematical foundations and integrate actual concepts from such fields as quantum mechanics, computer graphics, and natural language processing to deepen one's understanding

工作多年以后，重新整理学习一些关键数学基础，并将量子力学，计算机图形学，自然语言处理等领域的概念贯穿到其中，增进理解。

## [Dimensionality reduction technique and their insight in genomics and ecology](chapter01.ipynb)
From least-squares approach to linear ordination. Using PCA to obtained the same result and a view of PCA that is a multi-species extension of multiple (least-squares) regression.

**Dimensionality reduction technique and their application in genomics
and ecology**

Many data analyses methods can be understood in a view that data to be
explained in a way to response to straight lines, representing real
variables or hypothetical latent variables. And the latent variables may
eventually be explained by some facts such as populations the samples
belong to, geographic locations. Regression is a way to explore the
relations between variables and their response variables, and the
least-squares is a way to do linear regression. Least-squares approach
minimizes the sum of squared vertical distances; (suppose the relation
between x and y can be described as a line y=b1\*x+e) i.e. to find a
line Ey=b<sub>1\*</sub>x+e by estimating
$`b_{1}`$=$`\sum_{i = 1}^{N}{(y_{i} - \overline{y})}`$($`x_{i}`$-$`\overline{x}`$)/$`\sum_{i = 1}^{N}{(x_{i} - \overline{x})}^{2}`$
and minimizing residual sum
squares $`\ \sum_{i = 1}^{N}{(y_{i} - Ey_{i})}^{2}`$.

## Understanding PCA from SVD and performing dimension reduction using truncated SVD ##

## Understanding CA,CCA...


## From unsuprevised leaning to deeplearning

A fun 3D game demo using openGL to practice linear algebra