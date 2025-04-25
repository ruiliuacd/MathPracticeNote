# excise 3.1 Pool names
pools = ["V2", "B6", "B3", "B4", "VI", "B5B", "B8", "Bl", "D6", "B7", "B2", "D3", "D2", "Dl", "D5", "D6"]

# Frustulia count values
frustulia_count = np.array([0, 0, 14, 3, 0, 5, 6, 21, 62, 26, 14, 48, 97, 99, 28, 202])
Srel=np.array([0.78, 0.64, 0.69, 0.7, 0.64, 0.77, 0.73, 0.77, 0.58, 0.44, 0.44, 0.37, 0.23, 0.19, 0.31, 0.23])
# Compute ln(Frustulia count + 1)
yresp = np.log(frustulia_count + 1)

# Plot
plt.figure(figsize=(10, 5))
plt.scatter(Srel, yresp, color='skyblue')
plt.plot(Srel, yresp, color='red')
plt.xlabel("Pool")
plt.ylabel("ln(Frustulia count + 1)")
plt.title("Log-transformed Frustulia Count per Pool")
plt.xticks(rotation=45)
plt.grid(axis='y', linestyle='--', alpha=0.7)

# Show plot
plt.show()
if __name__ == '__main__':
    matrixA = np.column_stack((np.ones((Srel.shape[0], 1)), Srel))#np.column_stack((yresp, Srel))
    A_tA=matrixA.T @ matrixA#np.dot(np.transpose(matrixA), matrixA)
    A_tyresp=matrixA.T @ yresp
    k = np.linalg.solve(A_tA, A_tyresp)#get k : array([ 5.84834564, -5.96251375])