total_top_score = 0.0
total_avg_score = 0.0
total_time = 0.0

with open("657exp1_a_statNorm_1.log") as f:
    for line in f:
        if line[:4] == "Time":
            total_time += float(line[11:-9])

        if line[:15] == "total_avg_score":
            total_avg_score += float(line[17:].rstrip())

        if line[:15] == "total_top_score":
            total_top_score += float(line[17:].rstrip())

with open("657exp1_a_statNorm_2.log") as f:
    for line in f:
        if line[:4] == "Time":
            total_time += float(line[11:-9])

        if line[:15] == "total_avg_score":
            total_avg_score += float(line[17:].rstrip())

        if line[:15] == "total_top_score":
            total_top_score += float(line[17:].rstrip())

with open("657exp1_a_statNorm_3.log") as f:
    for line in f:
        if line[:4] == "Time":
            total_time += float(line[11:-9])

        if line[:15] == "total_avg_score":
            total_avg_score += float(line[17:].rstrip())

        if line[:15] == "total_top_score":
            total_top_score += float(line[17:].rstrip())

with open("657exp1_a_statNorm_4.log") as f:
    for line in f:
        if line[:4] == "Time":
            total_time += float(line[11:-9])

        if line[:15] == "total_avg_score":
            total_avg_score += float(line[17:].rstrip())

        if line[:15] == "total_top_score":
            total_top_score += float(line[17:].rstrip())

with open("657exp1_a_statNorm_5.log") as f:
    for line in f:
        if line[:4] == "Time":
            total_time += float(line[11:-9])

        if line[:15] == "total_avg_score":
            total_avg_score += float(line[17:].rstrip())

        if line[:15] == "total_top_score":
            total_top_score += float(line[17:].rstrip())

print("657exp1_a_statNorm: ")
print("total_avg_score: ", total_avg_score)
print("total_top_score: ", total_top_score)
print("total_time: ",  total_time)
print("average time: ", total_time/250.0)

print("-------------------")

total_top_score = 0.0
total_avg_score = 0.0
total_time = 0.0

with open("657exp1_b_modUCT.log") as f:
    for line in f:
        if line[:4] == "Time":
            total_time += float(line[11:-9])

        if line[:15] == "total_avg_score":
            total_avg_score += float(line[17:].rstrip())

        if line[:15] == "total_top_score":
            total_top_score += float(line[17:].rstrip())

print("657exp1_b_modUCT: ")
print("total_avg_score: ", total_avg_score)
print("total_top_score: ", total_top_score)
print("total_time: ",  total_time)
print("average time: ", total_time/250.0)

print("-------------------")

total_top_score = 0.0
total_avg_score = 0.0
total_time = 0.0

with open("657exp1_c_modUCTTopSc.log") as f:
    for line in f:
        if line[:4] == "Time":
            total_time += float(line[11:-9])

        if line[:15] == "total_avg_score":
            total_avg_score += float(line[17:].rstrip())

        if line[:15] == "total_top_score":
            total_top_score += float(line[17:].rstrip())

print("657exp1_c_modUCTTopSc: ")
print("total_avg_score: ", total_avg_score)
print("total_top_score: ", total_top_score)
print("total_time: ",  total_time)
print("average time: ", total_time/250.0)

print("-------------------")

total_top_score = 0.0
total_avg_score = 0.0
total_time = 0.0

with open("657exp2_a_Random.log") as f:
    for line in f:
        if line[:4] == "Time":
            total_time += float(line[11:-9])

        if line[:15] == "total_avg_score":
            total_avg_score += float(line[17:].rstrip())

        if line[:15] == "total_top_score":
            total_top_score += float(line[17:].rstrip())

print("657exp2_a_Random: ")
print("total_avg_score: ", total_avg_score)
print("total_top_score: ", total_top_score)
print("total_time: ",  total_time)
print("average time: ", total_time/250.0)

print("-------------------")

total_top_score = 0.0
total_avg_score = 0.0
total_time = 0.0

with open("657exp2_b_TabuRandom.log") as f:
    for line in f:
        if line[:4] == "Time":
            total_time += float(line[11:-9])

        if line[:15] == "total_avg_score":
            total_avg_score += float(line[17:].rstrip())

        if line[:15] == "total_top_score":
            total_top_score += float(line[17:].rstrip())

print("657exp2_b_TabuRandom: ")
print("total_avg_score: ", total_avg_score)
print("total_top_score: ", total_top_score)
print("total_time: ",  total_time)
print("average time: ", total_time/250.0)

print("-------------------")

total_top_score = 0.0
total_avg_score = 0.0
total_time = 0.0

with open("657exp2_c_TabuColRandom.log") as f:
    for line in f:
        if line[:4] == "Time":
            total_time += float(line[11:-9])

        if line[:15] == "total_avg_score":
            total_avg_score += float(line[17:].rstrip())

        if line[:15] == "total_top_score":
            total_top_score += float(line[17:].rstrip())

print("657exp2_c_TabuColRandom: ")
print("total_avg_score: ", total_avg_score)
print("total_top_score: ", total_top_score)
print("total_time: ",  total_time)
print("average time: ", total_time/250.0)

print("-------------------")

total_top_score = 0.0
total_avg_score = 0.0
total_time = 0.0

with open("657exp3_a_selectionUCT.log") as f:
    for line in f:
        if line[:4] == "Time":
            total_time += float(line[11:-9])

        if line[:15] == "total_avg_score":
            total_avg_score += float(line[17:].rstrip())

        if line[:15] == "total_top_score":
            total_top_score += float(line[17:].rstrip())

print("657exp3_a_selectionUCT: ")
print("total_avg_score: ", total_avg_score)
print("total_top_score: ", total_top_score)
print("total_time: ",  total_time)
print("average time: ", total_time/250.0)

print("-------------------")

total_top_score = 0.0
total_avg_score = 0.0
total_time = 0.0

with open("657exp3_b_selectionProgPrun_1.log") as f:
    for line in f:
        if line[:4] == "Time":
            total_time += float(line[11:-9])

        if line[:15] == "total_avg_score":
            total_avg_score += float(line[17:].rstrip())

        if line[:15] == "total_top_score":
            total_top_score += float(line[17:].rstrip())

with open("657exp3_b_selectionProgPrun_2.log") as f:
    for line in f:
        if line[:4] == "Time":
            total_time += float(line[11:-9])

        if line[:15] == "total_avg_score":
            total_avg_score += float(line[17:].rstrip())

        if line[:15] == "total_top_score":
            total_top_score += float(line[17:].rstrip())

with open("657exp3_b_selectionProgPrun_3.log") as f:
    for line in f:
        if line[:4] == "Time":
            total_time += float(line[11:-9])

        if line[:15] == "total_avg_score":
            total_avg_score += float(line[17:].rstrip())

        if line[:15] == "total_top_score":
            total_top_score += float(line[17:].rstrip())

with open("657exp3_b_selectionProgPrun_4.log") as f:
    for line in f:
        if line[:4] == "Time":
            total_time += float(line[11:-9])

        if line[:15] == "total_avg_score":
            total_avg_score += float(line[17:].rstrip())

        if line[:15] == "total_top_score":
            total_top_score += float(line[17:].rstrip())

with open("657exp3_b_selectionProgPrun_5.log") as f:
    for line in f:
        if line[:4] == "Time":
            total_time += float(line[11:-9])

        if line[:15] == "total_avg_score":
            total_avg_score += float(line[17:].rstrip())

        if line[:15] == "total_top_score":
            total_top_score += float(line[17:].rstrip())

print("657exp3_b_selectionProgPrun: ")
print("total_avg_score: ", total_avg_score)
print("total_top_score: ", total_top_score)
print("total_time: ",  total_time)
print("average time: ", total_time/250.0)

print("-------------------")

total_top_score = 0.0
total_avg_score = 0.0
total_time = 0.0

with open("657exp3_c_selectionHeur.log") as f:
    for line in f:
        if line[:4] == "Time":
            total_time += float(line[11:-9])

        if line[:15] == "total_avg_score":
            total_avg_score += float(line[17:].rstrip())

        if line[:15] == "total_top_score":
            total_top_score += float(line[17:].rstrip())

print("657exp3_c_selectionHeur: ")
print("total_avg_score: ", total_avg_score)
print("total_top_score: ", total_top_score)
print("total_time: ",  total_time)
print("average time: ", total_time/250.0)
