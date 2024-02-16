# HedgePlatform.Automation: Selenium to Playwright

A comprehensive guide on conversion of a Selenium project to Playwright with CoPilot + AI is a minefield for every developer willing to modernize their web automation projects. This will help provide step-by-step guidance in how to leverage CoPilot and AI technologies, and thereby smoothly transition from Selenium to its more modern, efficient Playwright framework, providing an easy upgrade path for automation testing environments.

In this tutorial, you will learn how to:
* Efficiently utilize CoPilot + AI by providing clear and precise prompts
* Convert Selenium based project to Playwright using (mostly) CoPilot.

There are several CoPilot prompts and expandable sections which may contain scripts and/or a lot of technical writing. Please be sure to review these sections!

## Before you start

A few considerations before starting...

Required:
- Visual Studio Code (recommended) or Visual Studio
- Access to Microsoft CoPilot
- Basic scripting skills
- Platform: Windows C# .NET / Playwright

> To install the Microsoft Cross Platform Build & Release Agent, run the following:
>
>> `$ dotnet add package Microsoft.Playwright --version 1.41.2`
>>
>> `$ playwright install`

Optional: 
- Other IDE's which support CoPilot (ie: IntelliJ)

### Overview of Roadmap
1. Convert Page Object Models
2. Convert Core Framework
3. Convert Test Steps
4. Resolve Build Errors

## Page Object Model Conversion

A big leap from Selenium into Playwright—faster execution, better API capabilities, better browser support within the moving world of web automation. This tutorial walks you through converting a Selenium project from the Page Object Model (POM) pattern to Playwright with CoPilot AI, transforming it into a more efficient and maintainable project.

### Page Object Model Structure:

In this guide, our POM structure is as follows.

- Solution
- - Project
- - - Pages
- - - - **Web Page** (ie: Login, Client Select, Dashboard)
- - - - - **Page Element** *
- - - - - **Page Element** *
- - - - **Supporting Page Stubs** (Extension functionality)

### Step 1: Copy Source Project "Page Object Model" cs Files

The first step in transitioning your project is to prepare your Selenium-based Page Object Model (POM) for conversion. 

Page Object Model (POM) is a web-based design pattern, basically creating an abstraction layer between test scripts and web pages, in the attempt to enhance test maintenance by providing a clear separation and code reusability.

1. Locate your Selenium POM cs Files
Find all the C# (.cs) files that are associated with your POM in the Selenium project. These are files that hold the definitions for your web page objects and interactions with them.
2. Create a New Project: Create a new project folder for your Playwright project, either with your most preferred IDE or through the command line.
3. Copy across all your .cs files from your Selenium project to the new Playwright project directory. Make sure to maintain the folder structure if that is organizing your page objects logically.
4. Install any necessary dependencies/NuGet packages/etc.

### Step 2: Refactor Source Files Using CoPilot AI

With your project files in place, the next step involves refactoring the copied Selenium POM cs files to be compatible with Playwright. 

While this section is the easiest, it is also the most tedious. 
_You will likely spend the majority of your time during the conversion process_.

> Here, CoPilot AI, a coding assistant, can significantly accelerate the refactoring process by providing code suggestions and automation capabilities.

1. Open Your IDE with CoPilot AI Integration: Ensure your development environment is equipped with CoPilot AI. Visual Studio Code, for example, offers an extension for GitHub Copilot.
2. Refactor cs Files: Open each cs file and initiate the refactoring process. Use CoPilot AI by typing a prompt that describes what you need, such as converting Selenium commands to Playwright.
3. Copy code


#### Example

**CoPilot Prompt**:

> Convert Selenium WebDriver commands to Playwright. 
> 
> Retarget page object models to the following format:
> 
> `[CssSelector("$selector")]`
> `public virtual $ElementName { get; set; }`
> 
> CoPilot AI will suggest changes, such as replacing Selenium's FindElement with Playwright’s Page.Locator method. Apply these suggestions to all elements of your POM cs files.


##### Original Code (C# - Login Page)

```
public IWebElement UsernameInput => this.FindElement("input#signInName");
public IWebElement PasswordInput => this.FindElement("input#password");
public IWebElement LoginButton => this.FindElement("#next");
```

##### CoPilot Suggested Code (C# - Login Page)

```
[CssSelector("input#signInName")]
public IWebElement UsernameInput { get; set; }

[CssSelector("input#password")]
public IWebElement PasswordInput { get; set; }

[CssSelector("#next")]
public IWebElement LoginButton => { get; set; }
```

In most cases, this is a straightforward enough process that little to no manual intervention is required.
By providing a template, CoPilot can easily understand the refactor intent.

<details>
  <summary><i>Breakdown</i></summary>

> Repeat for each .cs file 

1. In Visual Studio code, highlight the entire class.
2. Open CoPilot Chat (Control + I - VSCode Windows).
3. Enter CoPilot prompt.
4. Resolve any errors presented in refactored code.
5. Repeat ...
</details>

### Step 3: Refactor Test Execution Steps

Similar to Step 2, this task may be tedious but should be pretty straight-forward. For the most part, we are simply updating Selenium references to Playwright.

For most files, you simply need to instruct CoPilot to update Selenium methods to async Playwright methods.

**CoPilot Prompt**:

`
Update Selenium methods so that they call Playwright Async methods.
Update methods to be asynchronous where applicable.
`

<details>
<summary>Original C# Source</summary>

```
public void Login(string username, string password){
    this.UserInput.SendKeys(username);
    this.PasswordInput.SendKeys(password);
    this.LoginButton.Click();
}
```
</details>

<details>
<summary>Refactored C# Source</summary>


```
public async Task LoginAsync(string username, string password)
{
    var page = this.Page; // Assuming `Page` is your Playwright page object

    // Fill the username
    await this.UsernameInput.Fill(username); // Replace "#UserInputSelector" with the actual selector for the username input

    // Fill the password
    await this.PasswordInput.FillAsync(password); // Replace "#PasswordInputSelector" with the actual selector for the password input

    // Click the login button
    await this.LoginButton.ClickAsync(); // Replace "#LoginButtonSelector" with the actual selector for the login button
}
```
</details>

&nbsp;

> Apply this methodology to all test steps.

#### Core Framework Conversion

This section is highly dynamic, and heavily depends on the complexity of your project.

Generally though, you will only need to refactor Selenium related references to Playwright.

In the HedgePlatform project specifically, most of the core framework has been removed in favor of simplicity.

> **Virtual DOM Management**
> 
> The only significant portion of the framework refactored relates to managing the Virtual DOM


### Step 4: Build and Resolve Failures

After refactoring, you'll need to build your project to identify and resolve any issues stemming from the conversion process.

> **Build Your Project**: Use your IDE or the command line to build your Playwright project. This step will compile the code and highlight any errors or warnings.
>
> **Resolve Compilation Failures**: Pay close attention to the build output. You may encounter errors due to differences in Selenium and Playwright’s handling of web elements, asynchronous operations, or browser sessions. Use the error messages as a guide to make necessary adjustments.
>
> **Test for Runtime Errors**: Once your project successfully builds, run your tests to ensure they work as expected with Playwright. Given the differences between Selenium and Playwright, some tests might fail at runtime. Debug these failures, paying special attention to the changes in how Playwright interacts with web elements and manages page navigation and waits.
General Tips for Conversion
>
> **Know Playwright**: Understand what differentiates Playwright from Selenium, its API, and how to execute tests in order to easily convert to Playwright.

> **Refactor Incrementally**: Small, easy page objects should be taken up at the beginning of the conversion process and then slowly expanded to more complex page objects.

> **Utilize features of Playwright**: such as its auto-wait, the usage of selectors to shadow DOM, and built-in support for multiple contexts to give impetus to your tests.

By following these steps with using CoPilot AI for assistance, you can successfully migrate your Selenium project with the page object model into Playwright, taking advantage of all the new tooling and convenience for developers that Playwright offers.



# Bonus Guide: Enhancing test stability with CoPilot AI.

<details>

Update any references to Selenium using the same methodology in the previous step.


<summary>DOM State Challenges</summary>


# Complexities of Web Automation with Virtual DOM

Web automation on websites utilizing the Virtual DOM presents several complexities, primarily due to the dynamic nature of content rendering and interaction. The Virtual DOM, often used in modern web frameworks like React, enables efficient updates by only re-rendering components that have changed, rather than refreshing the entire page. This leads to challenges in web automation, such as:

## Dynamic Content Loading
Automated scripts might attempt to interact with elements that are not yet present or fully loaded in the DOM, causing errors or missed interactions. This necessitates the use of more sophisticated waiting strategies or event listeners to ensure elements are fully loaded before interaction.

## Element Identifiers
The Virtual DOM can lead to frequent changes in the structure and identifiers of DOM elements, making it difficult to create stable selectors for automated tests. Elements might have dynamically generated classes or IDs that change with each deployment, requiring automation frameworks to rely on more complex, often brittle, XPath or CSS selectors.

## Event Handling
Web applications using the Virtual DOM often have complex event handling mechanisms that can interfere with automation scripts. For example, synthetic events in React might not behave in the same way as native DOM events, leading to challenges in simulating user interactions accurately.

## State Management
The state-driven nature of applications using the Virtual DOM means that the visible UI can change drastically based on user interactions or data fetching. Automation scripts must be designed to adapt to these changes, ensuring that they can accurately assess and respond to the current state of the application.

## Performance Considerations
While the Virtual DOM improves user experience through efficient updates, automation scripts can inadvertently affect performance by triggering excessive re-renders. This can lead to false negatives in performance testing, where the automation impact rather than the application's performance becomes the bottleneck.

Addressing these complexities requires a nuanced approach to web automation, including the use of modern automation tools and frameworks that are designed to handle dynamic web applications, as well as careful planning and implementation of automation scripts to ensure they are resilient to the challenges posed by the Virtual DOM.

</details>

## Let's build a DOM State Handler using CoPilot

In this section, we will create a JavaScript script which gets injected into each webpage, and reports the state of the DOM (idle/active).

Flakiness caused by the DOM state (and Network state) is probably the most contributing factor to flaky tests in the context of Web Automation. 

> Let's tackle this before it becomes one in your new framework!

There are two parts to this part of the guide.

1. Generating a MutationObserver in JavaScript to capture changes in the DOM.
2. Delaying C# Playwright execution when the DOM is in an active state.


## Generating a MutationObserver in JavaScript

### Step 1 - Generating the MutationObserver

**CoPilot Prompt**:
`Generate a JavaScript Mutation Observer which captures only DOM elements added or removed.`

<details>
<summary>Updated JavaScript Source</summary>

```
/**
 * MutationObserver class to capture DOM elements added or removed.
 */
class DOMMutationObserver {
  /**
   * Creates an instance of DOMMutationObserver.
   * @param {function} callback - The callback function to be invoked when mutations occur.
   */
  constructor(callback) {
    this.callback = callback;
    this.observer = new MutationObserver(this.handleMutation.bind(this));
  }

  /**
   * Starts observing mutations in the DOM.
   */
  observe() {
    this.observer.observe(document.body, {
      childList: true, // Capture changes in the children of the observed node
      subtree: true    // Capture mutations in the entire subtree of the observed node
    });
  }

  /**
   * Handles mutations detected by the MutationObserver.
   * @param {MutationRecord[]} mutationsList - The list of mutations detected.
   */
  handleMutation(mutationsList) {
    mutationsList.forEach(mutation => {
      if (mutation.type === 'childList') {
        const addedNodes = Array.from(mutation.addedNodes);
        const removedNodes = Array.from(mutation.removedNodes);
        this.callback(addedNodes, removedNodes);
      }
    });
  }
}

// Example usage:
const observer = new DOMMutationObserver((addedNodes, removedNodes) => {
  console.log("Added nodes:", addedNodes);
  console.log("Removed nodes:", removedNodes);
});

observer.observe();
```
</details>

This is a pretty simple MutationObserver. At this point, it simply logs a message when nodes are added or removed. Let's make it a bit more complex, and have some way to check the DOM for its state.

### Step 2 - Adding 'data-dom-idle' attribute

There needs to be a way to save the DOM state so that it can be checked by the automation framework.

We simply need to update the DOM State after x time has passed since an add/remove node event has been triggered by the MutationObserver.

Ask CoPilot!

**CoPilot Prompt**:

```
Update the Mutation Observer so that:

- body includes an attribute 'data-dom-idle'
- data-dom-idle is updated to false on add/remove event.
- data-dom-idle is updated to true after 3 seconds of no add/remove event.

```

<details>
<summary>JavaScript Source</summary>

```
/**
 * MutationObserver class to capture DOM elements added or removed and update 'data-dom-idle' attribute.
 */
class DOMMutationObserver {
  /**
   * Creates an instance of DOMMutationObserver.
   * @param {function} callback - The callback function to be invoked when mutations occur.
   */
  constructor(callback) {
    this.callback = callback;
    this.observer = new MutationObserver(this.handleMutation.bind(this));
    this.domIdle = true;
    this.domIdleTimer = null;
  }

  /**
   * Starts observing mutations in the DOM.
   */
  observe() {
    this.observer.observe(document.body, {
      childList: true, // Capture changes in the children of the observed node
      subtree: true    // Capture mutations in the entire subtree of the observed node
    });
    this.updateDomIdle(false);
  }

  /**
   * Handles mutations detected by the MutationObserver.
   * @param {MutationRecord[]} mutationsList - The list of mutations detected.
   */
  handleMutation(mutationsList) {
    this.updateDomIdle(false);
    clearTimeout(this.domIdleTimer);
    this.domIdleTimer = setTimeout(() => {
      this.updateDomIdle(true);
    }, 3000);

    mutationsList.forEach(mutation => {
      if (mutation.type === 'childList') {
        const addedNodes = Array.from(mutation.addedNodes);
        const removedNodes = Array.from(mutation.removedNodes);
        this.callback(addedNodes, removedNodes);
      }
    });
  }

  /**
   * Updates the 'data-dom-idle' attribute of the body element.
   * @param {boolean} value - The value to set for the 'data-dom-idle' attribute.
   */
  updateDomIdle(value) {
    this.domIdle = value;
    document.body.setAttribute('data-dom-idle', value.toString());
  }
}

// Example usage:
const observer = new DOMMutationObserver((addedNodes, removedNodes) => {
  console.log("Added nodes:", addedNodes);
  console.log("Removed nodes:", removedNodes);
});

observer.observe();
```
</details>

In the updated code, two things are important to note.

- When an add/remove node event is triggered, a timer of 3 seconds is set before the `data-dom-idle` attribute is updated.
- Timer is cleared on new add/remove node event.


## Awaiting DOM Idle State in Playwright

In this section, we will:

- inject our javascript on each page load.
- generate a wrapper class for IElementHandle which can be used to enforce awaiting the DOM state without having to explicitly write out the code after each use of Playwright node methods (ie: Click, Fill, etc...)

### Step 1: Define and Inject MutationObserver Script

Open the location where your Playwright is instantiated, select all code, and generate the code to inject our script on init.




**CoPilot Prompt**:

```
In C# Playwright, inject local file 'MutationObserver.js', and add init script to Playwright.
```

<details>
<summary>C# Source</summary>

```
// Inject the MutationObserver.js script
await InjectLocalScriptAsync(page, "path/to/MutationObserver.js");
```
</details>

### Step 2: Generate Wrapper Class

The purpose of this wrapper class is to minimize the necessary code to await Dom state between Playwright actions such as Click, Fill, etc...

When a developer executes a DOM action, our framework should first wait for the DOM to report back `idle` state.

**CoPilot Prompt**:

```
Generate wrapper class for IElementHandle that overrides IElementHandle methods and await page.WaitForFunctionAsync("document.body.getAttribute('data-dom-idle') === 'true'").

- ClickAsync
- FillAsync
- HoverAsync
- IsHiddenAsync
- IsVisibleAsync
- PressAsync
- QuerySelectorAsync
- QuerySelectorAllAsync
- QuerySelectorAllHandleAsync
- ScreenshotAsync
- ScreenshotBase64Async
- ScreenshotDataAsync
- ScreenshotStreamAsync
- SelectAsync
- TapAsync
- TypeAsync
- UploadFileAsync
- WaitForSelectorAsync
- XPathAsync
```

<details>
<summary>C# Source</summary>

```
using System.IO;
using System.Threading.Tasks;
using Microsoft.Playwright;

public class ElementHandleWrapper : IElementHandle
{
    private readonly IElementHandle _elementHandle;
    private readonly IPage _page;

    public ElementHandleWrapper(IElementHandle elementHandle, IPage page)
    {
        _elementHandle = elementHandle;
        _page = page;
    }

    private async Task WaitForCustomConditionAsync()
    {
        await _page.WaitForFunctionAsync("document.body.getAttribute('data-dom-idle') === 'true'");
    }

    public async Task ClickAsync(ClickOptions? options = null)
    {
        await WaitForCustomConditionAsync();
        await _elementHandle.ClickAsync(options);
    }

    public async Task FillAsync(string value, FillOptions? options = null)
    {
        await WaitForCustomConditionAsync();
        await _elementHandle.FillAsync(value, options);
    }

    public async Task HoverAsync(HoverOptions? options = null)
    {
        await WaitForCustomConditionAsync();
        await _elementHandle.HoverAsync(options);
    }

    public Task<bool> IsHiddenAsync() => _elementHandle.IsHiddenAsync();

    public Task<bool> IsVisibleAsync() => _elementHandle.IsVisibleAsync();

    public async Task PressAsync(string key, PressOptions? options = null)
    {
        await WaitForCustomConditionAsync();
        await _elementHandle.PressAsync(key, options);
    }

    public Task<IElementHandle?> QuerySelectorAsync(string selector) => _elementHandle.QuerySelectorAsync(selector);

    public Task<IReadOnlyList<IElementHandle>> QuerySelectorAllAsync(string selector) => _elementHandle.QuerySelectorAllAsync(selector);

    public Task<IReadOnlyList<IElementHandle>> QuerySelectorAllHandleAsync(string selector) => _elementHandle.QuerySelectorAllHandleAsync(selector);

    public async Task<byte[]> ScreenshotAsync(ElementHandleScreenshotOptions? options = null)
    {
        await WaitForCustomConditionAsync();
        return await _elementHandle.ScreenshotAsync(options);
    }

    public async Task<string> ScreenshotBase64Async(ScreenshotType type = ScreenshotType.Png, ElementHandleScreenshotOptions? options = null)
    {
        await WaitForCustomConditionAsync();
        return await _elementHandle.ScreenshotBase64Async(type, options);
    }

    public async Task<byte[]> ScreenshotDataAsync(ElementHandleScreenshotOptions? options = null)
    {
        await WaitForCustomConditionAsync();
        return await _elementHandle.ScreenshotDataAsync(options);
    }

    public async Task<Stream> ScreenshotStreamAsync(ElementHandleScreenshotOptions? options = null)
    {
        await WaitForCustomConditionAsync();
        return await _elementHandle.ScreenshotStreamAsync(options);
    }

    public async Task<string[]> SelectAsync(string values, SelectOptionOptions? options = null)
    {
        await WaitForCustomConditionAsync();
        return await _elementHandle.SelectOptionAsync(values, options);
    }

    public async Task TapAsync(PointerActionOptions? options = null)
    {
        await WaitForCustomConditionAsync();
        await _elementHandle.TapAsync(options);
    }

    public async Task TypeAsync(string text, TypeOptions? options = null)
    {
        await WaitForCustomConditionAsync();
        await _elementHandle.TypeAsync(text, options);
    }

    public async Task UploadFileAsync(string path, FileChooserSetFilesOptions? options = null)
    {
        await WaitForCustomConditionAsync();
        await _elementHandle.SetInputFilesAsync(path, options);
    }

    public Task<IElementHandle?> WaitForSelectorAsync(string selector, WaitForSelectorOptions? options = null) => _elementHandle.WaitForSelectorAsync(selector, options);

    public Task<IReadOnlyList<IElementHandle>> XPathAsync(string expression) => _elementHandle.XPathAsync(expression);

    // Implement remaining IElementHandle members by directly delegating to _elementHandle
}
```
</details>

&nbsp;

Be sure to implement the usage of the wrapper class instead of the default IElementHandle implementation.
