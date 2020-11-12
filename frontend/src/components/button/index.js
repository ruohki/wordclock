import { h } from "preact";

const Button = ({ children, ...rest }) => {
  return (
    <button {...rest} class="button">{children}</button>
  );
}

export default Button;