package Lab5.Lab5;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class TextHandler 
{
    private final int width;

    public TextHandler(int width) 
    {
        this.width = width;
    }

    public String handleText(String text) 
    {
        String[] paragraphs = text.split('\n' + "\\s*" + '\n');
        
        List<String> handledParagraphs = new ArrayList<>();
        
        for (String paragraph : paragraphs) 
        {
            String handledParagraph = handleParagraph(paragraph);
            if (!handledParagraph.isEmpty()) 
            {
                handledParagraphs.add(handledParagraph);
            }
        }
        
        return String.join("\n\n", handledParagraphs);
    }

    private String handleParagraph(String paragraph) 
    {
        String normalizedText = paragraph.replaceAll("\\s+", " ").trim();

        if (normalizedText.isEmpty()) 
        {
            return "";
        }

        List<String> words = new ArrayList<>(Arrays.asList(normalizedText.split(" ")));
        
        List<String> handledLines = new ArrayList<>();
        List<String> currentLineWords = new ArrayList<>();
        int currentLineLength = 0;

        for (int i = 0; i < words.size(); i++) 
        {
            String word = words.get(i);
            int wordLength = word.length();
            
            boolean fits = (currentLineLength == 0) ? wordLength <= width : (currentLineLength + 1 + wordLength) <= width;

            if (fits) 
            {
                currentLineWords.add(word);
                currentLineLength = currentLineLength == 0 ? wordLength : currentLineLength + 1 + wordLength;
            } 
            else if (currentLineWords.isEmpty()) 
            {
                String part1 = word.substring(0, width - 1) + "-";
                String part2 = word.substring(width - 1);
                handledLines.add(part1);
                
                words.add(i + 1, part2);
            } 
            else 
            {
                handledLines.add(handleLine(currentLineWords, currentLineLength));
                currentLineWords.clear();
                currentLineLength = 0;
            }
        }

        if (!currentLineWords.isEmpty()) 
        {
            handledLines.add(handleLine(currentLineWords, currentLineLength));
        }

        return String.join("\n", handledLines);
    }

    private String handleLine(List<String> words, int currentLength) 
    {
        if (words.size() <= 1) 
        {
            return String.join(" ", words);
        }

        int totalSpacesNeeded = width - currentLength;
        int numGaps = words.size() - 1;
        
        int baseSpacesPerGap = totalSpacesNeeded / numGaps;
        
        int extraSpacesGaps = totalSpacesNeeded % numGaps;
        
        StringBuilder handledLine = new StringBuilder();

        for (int i = 0; i < words.size(); i++) 
        {
            handledLine.append(words.get(i));

            if (i < numGaps) 
            {
                for (int j = 0; j < 1 + baseSpacesPerGap; j++) 
                {
                    handledLine.append(" ");
                }
                
                if (i < extraSpacesGaps) 
                {
                    handledLine.append(" ");
                }
            }
        }

        return handledLine.toString();
    }
}