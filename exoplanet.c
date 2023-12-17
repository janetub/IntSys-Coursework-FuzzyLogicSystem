#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// Define constants for linguistic variables and membership functions
// Depth of Dip (parts per million, ppm)
#define DEPTH_SMALL_START 0
#define DEPTH_SMALL_PEAK 500
#define DEPTH_SMALL_END 1000

#define DEPTH_MEDIUM_START 500
#define DEPTH_MEDIUM_PEAK 1500
#define DEPTH_MEDIUM_END 2000

#define DEPTH_LARGE_START 1500
#define DEPTH_LARGE_PEAK 2500
#define DEPTH_LARGE_END 3000

// Duration of Dip (hours)
#define DURATION_SHORT_START 0
#define DURATION_SHORT_PEAK 1
#define DURATION_SHORT_END 2

#define DURATION_MEDIUM_START 1.5
#define DURATION_MEDIUM_PEAK 3
#define DURATION_MEDIUM_END 4.5

#define DURATION_LONG_START 4
#define DURATION_LONG_PEAK 5
#define DURATION_LONG_END 6

// Interval Between Dips (days)
#define INTERVAL_SHORT_START 0
#define INTERVAL_SHORT_PEAK 1
#define INTERVAL_SHORT_END 2

#define INTERVAL_MEDIUM_START 1.5
#define INTERVAL_MEDIUM_PEAK 3
#define INTERVAL_MEDIUM_END 4.5

#define INTERVAL_LONG_START 4
#define INTERVAL_LONG_PEAK 5
#define INTERVAL_LONG_END 6

// Exoplanet Likelihood (probability)
#define LIKELIHOOD_UNLIKELY_START 0
#define LIKELIHOOD_UNLIKELY_PEAK 0.25
#define LIKELIHOOD_UNLIKELY_END 0.75

#define LIKELIHOOD_LIKELY_START 0.25
#define LIKELIHOOD_LIKELY_PEAK 0.75
#define LIKELIHOOD_LIKELY_END 1


// Define structure for fuzzified values
typedef struct
{
    float start;
    float peak;
    float end;
} FuzzifiedValues;

// Define structures for fuzzy rules
typedef struct
{
    float depth;
    float duration;
    float interval;
    float likelihood;
} FuzzyRule;

typedef struct FuzzyRuleNode
{
    FuzzyRule rule;
    struct FuzzyRuleNode *next;
} FuzzyRuleNode;

// Fuzzification
FuzzifiedValues* fuzzifyDepth(float depth) 
{
    FuzzifiedValues *fuzzyDepth = (FuzzifiedValues*)malloc(sizeof(FuzzifiedValues));

    // small
    if (DEPTH_SMALL_START <= depth && depth <= DEPTH_SMALL_PEAK){
        fuzzyDepth->start = (depth - DEPTH_SMALL_START)/(DEPTH_SMALL_PEAK - DEPTH_SMALL_START);
    } else if (DEPTH_SMALL_PEAK < depth && depth < DEPTH_SMALL_END){
        fuzzyDepth->start = (DEPTH_SMALL_END - depth)/(DEPTH_SMALL_END - DEPTH_SMALL_PEAK);
    } else{
        fuzzyDepth->start = 0;
    }

    // medium
    if (DEPTH_MEDIUM_PEAK < depth && depth < DEPTH_MEDIUM_END){
        fuzzyDepth->peak = (DEPTH_MEDIUM_END - depth)/(DEPTH_MEDIUM_END - DEPTH_MEDIUM_PEAK);
    } else if (DEPTH_MEDIUM_START < depth && depth <= DEPTH_MEDIUM_PEAK){
        fuzzyDepth->peak = (depth - DEPTH_MEDIUM_START)/(DEPTH_MEDIUM_PEAK - DEPTH_MEDIUM_START);
    } else{
        fuzzyDepth->peak = 0;
    }

    // large
    if (DEPTH_LARGE_START < depth && depth <= DEPTH_LARGE_PEAK){
        fuzzyDepth->end = (depth - DEPTH_LARGE_START)/(DEPTH_LARGE_PEAK - DEPTH_LARGE_START);
    } else if (DEPTH_LARGE_PEAK < depth && depth <= DEPTH_LARGE_END){
        fuzzyDepth->end = (DEPTH_LARGE_END - depth)/(DEPTH_LARGE_END - DEPTH_LARGE_PEAK);
    } else{
        fuzzyDepth->end = 0;
    }

    return fuzzyDepth;
}

FuzzifiedValues* fuzzifyDuration(float duration) 
{
    FuzzifiedValues *fuzzyDuration = (FuzzifiedValues*)malloc(sizeof(FuzzifiedValues));

    // short
    if (DURATION_SHORT_START <= duration && duration <= DURATION_SHORT_PEAK){
        fuzzyDuration->start = (duration - DURATION_SHORT_START)/(DURATION_SHORT_PEAK - DURATION_SHORT_START);
    } else if (DURATION_SHORT_PEAK < duration && duration < DURATION_SHORT_END){
        fuzzyDuration->start = (DURATION_SHORT_END - duration)/(DURATION_SHORT_END - DURATION_SHORT_PEAK);
    } else{
        fuzzyDuration->start = 0;
    }

    // medium
    if (DURATION_MEDIUM_START <= duration && duration <= DURATION_MEDIUM_PEAK){
        fuzzyDuration->peak = (duration - DURATION_MEDIUM_START)/(DURATION_MEDIUM_PEAK - DURATION_MEDIUM_START);
    } else if (DURATION_MEDIUM_PEAK < duration && duration < DURATION_MEDIUM_END){
        fuzzyDuration->peak = (DURATION_MEDIUM_END - duration)/(DURATION_MEDIUM_END - DURATION_MEDIUM_PEAK);
    } else{
        fuzzyDuration->peak = 0;
    }

    // long
    if (DURATION_LONG_START <= duration && duration <= DURATION_LONG_PEAK){
        fuzzyDuration->end = (duration - DURATION_LONG_START)/(DURATION_LONG_PEAK - DURATION_LONG_START);
    } else if (DURATION_LONG_PEAK < duration && duration <= DURATION_LONG_END){
        fuzzyDuration->end = (DURATION_LONG_END - duration)/(DURATION_LONG_END - DURATION_LONG_PEAK);
    } else{
        fuzzyDuration->end = 0;
    }

    return fuzzyDuration;
}

FuzzifiedValues* fuzzifyInterval(float interval) 
{
    FuzzifiedValues *fuzzyInterval = (FuzzifiedValues*)malloc(sizeof(FuzzifiedValues));

    // short
    if (INTERVAL_SHORT_START <= interval && interval <= INTERVAL_SHORT_PEAK){
        fuzzyInterval->start = (interval - INTERVAL_SHORT_START)/(INTERVAL_SHORT_PEAK - INTERVAL_SHORT_START);
    } else if (INTERVAL_SHORT_PEAK < interval && interval < INTERVAL_SHORT_END){
        fuzzyInterval->start = (INTERVAL_SHORT_END - interval)/(INTERVAL_SHORT_END - INTERVAL_SHORT_PEAK);
    } else{
        fuzzyInterval->start = 0;
    }

    // medium
    if (INTERVAL_MEDIUM_START <= interval && interval <= INTERVAL_MEDIUM_PEAK){
        fuzzyInterval->peak = (interval - INTERVAL_MEDIUM_START)/(INTERVAL_MEDIUM_PEAK - INTERVAL_MEDIUM_START);
    } else if (INTERVAL_MEDIUM_PEAK < interval && interval < INTERVAL_MEDIUM_END){
        fuzzyInterval->peak = (INTERVAL_MEDIUM_END - interval)/(INTERVAL_MEDIUM_END - INTERVAL_MEDIUM_PEAK);
    } else{
        fuzzyInterval->peak = 0;
    }

    // long
    if (INTERVAL_LONG_START <= interval && interval <= INTERVAL_LONG_PEAK){
        fuzzyInterval->end = (interval - INTERVAL_LONG_START)/(INTERVAL_LONG_PEAK - INTERVAL_LONG_START);
    } else if (INTERVAL_LONG_PEAK < interval && interval <= INTERVAL_LONG_END){
        fuzzyInterval->end = (INTERVAL_LONG_END - interval)/(INTERVAL_LONG_END - INTERVAL_LONG_PEAK);
    } else{
        fuzzyInterval->end = 0;
    }

    return fuzzyInterval;
}

void cleanString(char* str)
{
    // clean by lowercasing chars and removing non-letter characters
    for (char* p = str; *p; ++p) 
    {
        if (isalpha((unsigned char)*p) || isspace((unsigned char)*p)) {
            *p = tolower(*p);
        } else {
            *p = ' ';
        }
    }

    // remove extra spaces
    int i = 0, j = 0;
    while (str[i])
    {
        if (!isspace((unsigned char)str[i]) || (i > 0 && !isspace((unsigned char)str[i - 1])))
        {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

// Rules
void addRule(FuzzyRuleNode** head, FuzzyRule* rule)
{
    FuzzyRuleNode *new = (FuzzyRuleNode*)malloc(sizeof(FuzzyRuleNode));
    new->rule = *rule;
    new->next = *head; // insert new node at the beginning
    *head = new;
}

FuzzyRule* parseRule(char* line, FuzzifiedValues depth, FuzzifiedValues duration, FuzzifiedValues interval) 
{
    FuzzyRule *rule = (FuzzyRule*)malloc(sizeof(FuzzyRule));

    cleanString(line);

    char* token = strtok(line, " ");  // split to tokens
     while (token != NULL) 
     {
        if (strcmp(token, "if") == 0) // parse antecedent part of rule
        { 
            while ((token = strtok(NULL, " ")) != NULL && strcmp(token, "then") != 0) 
            {
                char* field = token;
                char* value = NULL;

                while ((token = strtok(NULL, " ")) != NULL && strcmp(token, "and") != 0 && strcmp(token, "then") != 0)
                {
                    value = token;
                }

                if (field && value)
                {
                    if (strcmp(field, "depth") == 0) {
                        if (strcmp(value, "small") == 0) {
                            rule->depth = depth.start;
                        } else if (strcmp(value, "medium") == 0) {
                            rule->depth = depth.peak;
                        } else if (strcmp(value, "large") == 0) {
                            rule->depth = depth.end;
                        }
                    } else if (strcmp(field, "duration") == 0) {
                        if (strcmp(value, "short") == 0) {
                            rule->duration = duration.start;
                        } else if (strcmp(value, "medium") == 0) {
                            rule->duration = duration.peak;
                        } else if (strcmp(value, "long") == 0) {
                            rule->duration = duration.end;
                        }
                    } else if (strcmp(field, "interval") == 0) {
                        if (strcmp(value, "short") == 0) {
                            rule->interval = interval.start;
                        } else if (strcmp(value, "medium") == 0) {
                            rule->interval = interval.peak;
                        } else if (strcmp(value, "long") == 0) {
                            rule->interval = interval.end;
                        }
                    }
                }

                if(strcmp(token, "then") == 0)
                    break;
            }
        }

        if(strcmp(token, "then") == 0)
        {
            while((token = strtok(NULL, " ")) != NULL) // continue tokenizing the same string and return string as one token
            {
                if (strcmp(token, "likely") == 0) 
                {
                    rule->likelihood = 1;
                    break;
                }
                else if (strcmp(token, "unlikely") == 0)
                {
                    rule->likelihood = -1; // negative value means unlikely
                    break;
                }
            }
        }

        token = strtok(NULL, " ");
    }

    return rule;
}


void loadRulesFromFile(const char* filename, FuzzyRuleNode** ruleList, FuzzifiedValues depth, FuzzifiedValues duration, FuzzifiedValues interval)
{
    FILE* file = fopen(filename, "r");
    if(file == NULL)
    {
        printf("Could not open file %s\n", filename);
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1) // read each line
    {
        FuzzyRule *rule = parseRule(line, depth, duration, interval);
        addRule(ruleList, rule);
        free(rule);
    }

    free(line);
    fclose(file);
}

// Inference Engine

void infer(FuzzyRule* rule) 
{
    // fuzzy operator in the antecedent
    rule->likelihood *= fminf(rule->depth, fminf(rule->duration, rule->interval)); // negative value means unlikely, otherwise likely
}

void inferAll(FuzzyRuleNode* ruleList) 
{
    FuzzyRuleNode* currentNode = ruleList;
    while (currentNode != NULL) 
    {
        infer(&(currentNode->rule));
        currentNode = currentNode->next;
    }
}

// Aggregation
float aggregateLikely(FuzzyRuleNode* ruleList) 
{
    float aggregatedLikelihood = 0;

    FuzzyRuleNode* currentNode = ruleList;
    while (currentNode != NULL) 
    {
        int isMax = currentNode->rule.likelihood > 0 && currentNode->rule.likelihood > aggregatedLikelihood;
        if (isMax) 
        {
            aggregatedLikelihood = currentNode->rule.likelihood;
        }
        currentNode = currentNode->next;
    }

    return aggregatedLikelihood;
}

float aggregateUnlikely(FuzzyRuleNode* ruleList) 
{
    float aggregatedLikelihood = 0;

    FuzzyRuleNode* currentNode = ruleList;
    while (currentNode != NULL) 
    {
        int isMax = currentNode->rule.likelihood < 0 && currentNode->rule.likelihood < aggregatedLikelihood;
        if (isMax) 
        {
            aggregatedLikelihood = currentNode->rule.likelihood;
        }
        currentNode = currentNode->next;
    }

    return aggregatedLikelihood;
}


// Defuzzification (centroid method)
float defuzzify(float likely, float unlikely, int n) 
{
    float sum_weights = 0;
    float sum_values = 0;
    for (int i = 0; i <= n; i++) 
    {
        float x = (float)i / n;  // divides UOD into n divisions
        float membership = (i <= n/2)? unlikely : likely;  // assigns degree of membership acc on where it falls
        sum_weights += membership;
        sum_values += x * membership;
    }
    return sum_values / sum_weights;  // weighted average
}

void freeRules(FuzzyRuleNode* head) 
{
    FuzzyRuleNode* current = head;
    while (current != NULL) {
        FuzzyRuleNode* next = current->next;
        free(current);
        current = next;
    }
}

void printRules(FuzzyRuleNode* head)
{
    FuzzyRuleNode* temp = head;
    while(temp != NULL)
    {
        printf("Depth: %f, Duration: %f, Interval: %f, Likelihood: %f\n", temp->rule.depth, temp->rule.duration, temp->rule.interval, temp->rule.likelihood);
        temp = temp->next;
    }
}

void printNodeCount(FuzzyRuleNode* head)
{
    int count = 0;
    FuzzyRuleNode* temp = head;
    while(temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    printf("Number of nodes in the list: %d\n", count);
}

int main() {
    // crisp input values
    float depth = 450;
    float duration = 4.2;
    float interval = 1;
    float threshold = 0.5;
    int divs = 1000;

    // fuzzification
    FuzzifiedValues* fuzzyDepth = fuzzifyDepth(depth);
    printf("Depth: %f = [%f, %f, %f]\n", depth, fuzzyDepth->start, fuzzyDepth->peak, fuzzyDepth->end);

    FuzzifiedValues* fuzzyDuration = fuzzifyDuration(duration);
    printf("Duration: %f = [%f, %f, %f]\n", duration, fuzzyDuration->start, fuzzyDuration->peak, fuzzyDuration->end);

    FuzzifiedValues* fuzzyInterval = fuzzifyInterval(interval);
    printf("Interval: %f = [%f, %f, %f]\n", interval, fuzzyInterval->start, fuzzyInterval->peak, fuzzyInterval->end);

    FuzzyRuleNode** ruleList = (FuzzyRuleNode**)malloc(sizeof(FuzzyRuleNode*)*12);
    for(int i = 0; i < 12; i++)
    {
        ruleList[i] = NULL;
    }

    // rule base
    loadRulesFromFile("rules.txt", ruleList, *fuzzyDepth, *fuzzyDuration, *fuzzyInterval);

    // inference
    inferAll(*ruleList);

    // aggregation
    float fuzzyLikely = aggregateLikely(*ruleList);
    float fuzzyUnlikely = aggregateUnlikely(*ruleList);

    printf("Likelihood = [%f, %f]\n", fuzzyUnlikely, fuzzyLikely);

    float crispOutput = defuzzify(fuzzyLikely, fuzzyUnlikely, divs);

    printf("Crisp value\t: %f\nRepresentation\t: The detected celestial object is %s exoplanet.", crispOutput, crispOutput > threshold? "an": "not an");

    free(fuzzyDepth);
    free(fuzzyDuration);
    free(fuzzyInterval);
    freeRules(*ruleList);
    free(ruleList);
    return 0;
}