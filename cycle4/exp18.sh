#!/bin/sh

# CS 17L2 NETWORKS AND OPERATING SYSTEMS LABORATORY
# Cycle 4 : Exp 18 : SHELL PROGRAMMING - I
# ADARSH P.K. CSU13203
# Calculates the SGPA, CGPA, credits and number of failed subjects.

awk -F' ' '
BEGIN{ print "SL.NO.\tCREDITS\tFAILED\tS1GPA\tS2GPA\tCGPA" > "output" }
{
    if(FILENAME=="s1s2.credits.txt")
        if(FNR==1)
            for(i = 1; i <= NF; i++)
                a[i]=$i
        else
            for(i = 1; i <= NF; i++)
                credits[a[i]]=$i
    else
    {
        if(FNR==1)
        {
            denominator=0
            for(i = 1; i <= NF; i++)
            {
                a[i]=$i
                denominator += credits[$i]
            }
        }
        else
        {
            count=FNR
            numerator = 0
            for(i = 1; i <= NF; i++)
            {
                if($i!="F" && $i!="FE" && $i!="I")
                    scoredcredit[FNR-1] += credits[a[i]]
                else
                    nofailed[FNR-1]++

                if($i== "O[S]" || $i=="O")
                    numerator += 10*credits[a[i]]
                else if($i== "A+")
                    numerator += 9*credits[a[i]]
                else if($i== "A")
                    numerator += 8*credits[a[i]]
                else if($i== "B+")
                    numerator += 7*credits[a[i]]
                else if($i== "B")
                    numerator += 6*credits[a[i]]
                else if($i== "C")
                    numerator += 5*credits[a[i]]
                else if($i== "P")
                    numerator += 4*credits[a[i]]
            }
            if(gpa[FNR-1] == "")
            {
                s1gpa[FNR-1] = numerator/denominator
                gpa[FNR-1] = s1gpa[FNR-1]
            }
            else
            {
                s2gpa[FNR-1] = numerator/denominator
                gpa[FNR-1] = (gpa[FNR-1]+s2gpa[FNR-1])/2
            }
        }
    }
}
END{
    for(i=1;i<count;i++)
        printf"%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n",i,scoredcredit[i],nofailed[i],s1gpa[i],s2gpa[i],gpa[i] >> "output"
    print "See output file for results."
}
' s1s2.credits.txt s1.txt s2.txt

# printf"%d GPA is : ", FNR-1
# printf"%.2f\n", (numerator/denominator)