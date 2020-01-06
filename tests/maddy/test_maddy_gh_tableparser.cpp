/*
 * This project is licensed under the MIT license. For more information see the
 * LICENSE file.
 */
#include <memory>

#include "gmock/gmock.h"

#include "maddy/gh_tableparser.h"

// -----------------------------------------------------------------------------

class MADDY_GH_TABLEPARSER : public ::testing::Test
{
protected:
  std::shared_ptr<maddy::GitHubTableParser> tableParser;

  void
  SetUp() override
  {
    this->tableParser = std::make_shared<maddy::GitHubTableParser>(
      nullptr,
      nullptr
    );
  }
};

// -----------------------------------------------------------------------------

TEST_F(MADDY_GH_TABLEPARSER, IsStartingLineReturnsTrueWhenFacedWithTheBeginningOfATable)
{
  ASSERT_EQ(true, maddy::GitHubTableParser::IsStartingLine("| Some | Table |"));
}

TEST_F(MADDY_GH_TABLEPARSER, IsFinishedReturnsFalseInTheBeginning)
{
  ASSERT_FALSE(tableParser->IsFinished());
}

TEST_F(MADDY_GH_TABLEPARSER, ItReplacesMarkdownWithAnHtmlTable)
{
  std::vector<std::string> markdown = {
    "|Left header|middle header|last header|"
    , "|-|-|-|"
    , "|cell 1|cell 2|cell 3|"
    , "|cell 4|cell 5|cell 6|"
    , ""
  };
  std::string expected = "<table><thead><tr><th>Left header</th><th>middle header</th><th>last header</th></tr></thead><tbody><tr><td>cell 1</td><td>cell 2</td><td>cell 3</td></tr><tr><td>cell 4</td><td>cell 5</td><td>cell 6</td></tr></tbody></table>";

  for (std::string md : markdown)
  {
    tableParser->AddLine(md);
  }

  ASSERT_TRUE(tableParser->IsFinished());

  std::stringstream& output(tableParser->GetResult());

  const std::string& outputString = output.str();

  ASSERT_EQ(expected, outputString);
}
