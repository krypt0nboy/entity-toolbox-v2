<?php

/**
 * Class _CodePrinter
 */
class _CodePrinter {
  // Required traits.
  use EntityToolboxCommonTraits, TemplatingTraits, ModuleDependentTraits;

  // Constant to get the engine programming language.
  const PROGRAMMING_LANG = '';
  // Open tag for the engine's language.
  const OPEN_TAG = '';
  // Closing tag for the engine's language.
  const CLOSE_TAG = '';
  // Function tag.
  const FUNCTION_TAG = '';
  // Variable prefix.
  // Eg : "$" is placed before a php variable.
  const VAR_PREFIX = '';

  /**
   * @var string $templateUri
   *   The engine's template path.
   */
  protected $templateUri;
  /**
   * @var resource $templateFile
   *   The engine's template file.
   */
  protected $templateFile;
  /**
   * @var string $originCode
   *   A piece of code to write on.
   */
  protected $originCode;
  /**
   * @var string $originFileName
   *   The original code file name.
   *   The name of the file containing the original code.
   */
  protected $originFileName;
  /**
   * @var resource $origin
   *   The file containing the original code.
   */
  protected $origin;
  /**
   * @var string $output
   *   The final output.
   */
  protected $output;


  /**
   * _CodePrinter constructor.
   */
  public function _CodePrinter() {

  }
}

/**
 * Class PHPCodePrinter
 */
class PHPCodePrinter extends _CodePrinter {
  // Constant to get the engine programming language.
  const PROGRAMMING_LANG = 'php';
  // Open tag for the engine's language.
  const OPEN_TAG = '<?php';
  // Closing tag for the engine's language.
  const CLOSE_TAG = '?>';
  // Function tag.
  const FUNCTION_TAG = 'function';
  // Variable prefix.
  // Eg : "$" is placed before a php variable.
  const VAR_PREFIX = '$';
}