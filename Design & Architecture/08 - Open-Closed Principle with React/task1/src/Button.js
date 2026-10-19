const Button = ({style, label, action}) => {
    return (
        <button onClick={action} style={style}>{label}</button>
    );
} 

export default Button;